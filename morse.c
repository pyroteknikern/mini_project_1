#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdlib.h>
#include "morse.h"
#include "String.h"

Dictionary dictionary;
CoderDecoder coderDecoder;
 // Gloabal varaibles is not good to use. We use it here so that we don't pass it all the function calls. This issue will be resolved when we use pointers in the part 2 of this project.


void displayHelp() {
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
void initializeDictionary() {
    dictionary.id = 0;
    dictionary.size = MAX_DICTIONARY_SIZE;
    char chars[MAX_DICTIONARY_SIZE] = "1234567890abcdefghijklmnopqrstuvwxyz";
    strcpy(dictionary.characters, chars);
    char *mc[MAX_DICTIONARY_SIZE] = {".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    memcpy(dictionary.morseCodes, mc, sizeof(mc));
}


/*
 * translates an ASCII character to morse code
 * param1: character you want to translate into morse
 * param2: pointer to a string that will be populated with morse
*/
int getMorseCode(const char character, char *morseChar){
    strcpy(morseChar, "");
    for(int i = 0; i < coderDecoder.dictionary.size; i++) {
        if(coderDecoder.caseSensitive) {
            if(character == coderDecoder.dictionary.characters[i]) {
                strcpy(morseChar, coderDecoder.dictionary.morseCodes[i]);
                return 1;
            }
        }
        else {
            if(tolower(character) == coderDecoder.dictionary.characters[i]) {
                strcpy(morseChar, coderDecoder.dictionary.morseCodes[i]);
                return 1;
            }
        }
    }
    return -1;
}

/*
 * initializses the global CoderDecoder struct
*/
void initializeCoderDecoder(){
    coderDecoder.dictionary = dictionary;
    coderDecoder.caseSensitive = true;
    coderDecoder.currentDictionaryId = dictionary.id;
}

/*
 * encodes an ASCII string to morse code
 * param1: string you want to translate
 * param2: pointer to the string you want to populate with morse code
 * note: param2 not having enough memory can lead to undefined behaviour
*/
int encodeToMorse(const char *text, char *encodedText) {
    encodedText[0] = '\0';
    char morseChar[MAX_MORSE_CHAR_LENGTH] = "";
    for(int i = 0; i < strlen(text); i++) {
        if(getMorseCode(text[i], morseChar) == -1) return -1;
        strcat(encodedText, morseChar);
        strcat(encodedText, " ");
    }
    return 1;
}

/*
 * translate morse code to ASCII character
 * param1: string that contains morse code
 * param2: pointer to character that will be populated by the translated morse code
 */

int getCharFromMorse(const char* morseChar, char* character) {
    for(int i = 0; i < coderDecoder.dictionary.size; i++) {
        if(strcmp(coderDecoder.dictionary.morseCodes[i], morseChar) == 0) {
            *character = coderDecoder.dictionary.characters[i];
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
int decodeFromMorse(const char *morseCode, char *decodedText) {
    char morseChar[MAX_MORSE_CHAR_LENGTH + 1] = "";
    char placeholderChar;
    for(int i = 0; i < strlen(morseCode) + 1; i++) {
        if(morseCode[i] == ' ' || morseCode[i] == '\0') {
            if(getCharFromMorse(morseChar, &placeholderChar) == -1) return -1;
            strncat(decodedText, &placeholderChar, 1);
            morseChar[0] = '\0';
            placeholderChar = '\0';
            continue;
        }
        strncat(morseChar, &morseCode[i], 1);
    }
    return 1;
}

void encode_file_to_file(FILE* source, FILE* dest) {
    char ch;
    char morseChar[MAX_MORSE_CHAR_LENGTH] = ""; 
    int res;
    while((ch = getc(source)) != EOF) {
        res = getMorseCode(ch, morseChar);
        if(res == 1) fprintf(dest, "%s ", morseChar);
        //if(res == -1) fprintf(dest, "X");
    }
    fflush(dest);
}

void test() {
    FILE* f1;
    FILE* f2;
    f1 = fopen("file1.txt", "r");
    f2 = fopen("file2.txt", "w+");
    encode_file_to_file(f1, f2);
}
    
/*
 * prints Dictionary in two columns
 */
void printDictionary() {
    printf("Morse\tAlphabet\n");
    for(int i = 0; i < coderDecoder.dictionary.size; i++) {
        printf("%s\t%c\n", coderDecoder.dictionary.morseCodes[i], coderDecoder.dictionary.characters[i]);
    }
}

/*
 * changes decoder sensitivity
 * param1: true for case sensitive false for insensitive
 */
void setMode(bool caseSensitive) {
    coderDecoder.caseSensitive = caseSensitive;
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
 * command decode
 */
void decode() {
    String input_str = new_string();
    bool run = true;
    while(run) {
        printf("\nEnter text you want to decode\n(decoder) >> ");
        file_to_string(&input_str, stdin);
        trunk_trailing_spaces(input_str.str);
        char* decodedString = malloc((nr_of_seg(input_str.str, ' ') + 1) * sizeof(char));
        decodedString[0] = '\0';
        if(strcmp(input_str.str, "-exit") == 0) {
            printf("Exiting decoder mode...\n");
            run = false;
        }
        else if(strcmp(input_str.str, "-o") == 0)
            printf("- '-exit' exit decoder mode\n");
        else {
            if(decodeFromMorse(input_str.str, decodedString) != 1) 
                printf("\nyou can only enter '.' and '-' and ' ' to separate characters\n\n");
            else {
                printf("\nDecoded: %s\n\n\n", decodedString);
            }
        }
        free(decodedString);
    }
    destroy_string(&input_str);
}

/*
 * encode text file to morse code alternative print file
 */
void encode_from_file() {
    printf("Enter name of file to encode\n>> "); 
    String input_str = new_string();
    file_to_string(&input_str, stdin);
    trunk_trailing_spaces(input_str.str);
    FILE* source = fopen(input_str.str, "r");
    if(source == NULL) {
        printf("\nFile was not found\n");
        destroy_string(&input_str);
        return;
    }
    FILE* destination;
    printf("Would you like to print result to a file? (y/n)\n>> ");
    
    bool y_n = true;
    char y_n_char;
    while(y_n) {
        y_n_char = getc(stdin);
        getc(stdin); //newline
        if(y_n_char == 'n') {
            destination = stdout;
            break;
        }
        if(y_n_char == 'y') {
            printf("Enter filename to print encoded result\n>>");
            file_to_string(&input_str, stdin);
            trunk_trailing_spaces(input_str.str);
            destination = fopen(input_str.str, "w+");
            break;
        }
    }
    printf("\nUnrecognizable characters will be ignored\n\n");
    encode_file_to_file(source, destination);
    if(destination != stdout) fclose(destination);
    fclose(source);
    destroy_string(&input_str);
}
/*
 * command encode
 */
void encode() {
    String input_str = new_string();
    bool run = true;
    while(run) {
        printf("\nEnter text you want to encode (options '-o')\n(encoder) >> ");
        file_to_string(&input_str, stdin);
        trunk_trailing_spaces(input_str.str);
        if(strcmp(input_str.str, "-exit") == 0) {
            printf("Exiting encoder mode...\n");
            break;
        }
        else if(strcmp(input_str.str, "-o") == 0) {
            printf("- '-f' encode text from file\n");
            printf("- '-exit' exit\n");
        }
        else if(strcmp(input_str.str, "-f") == 0)
            encode_from_file();
        else {
            char* encodedString = malloc((input_str.length * MAX_MORSE_CHAR_LENGTH + 1) * sizeof(char));
            encodedString[0] = '\0';
            if(encodeToMorse(input_str.str, encodedString) == -1) 
                printf("Enter only letters and or numbers\n");
            else
                printf("\nMorse: %s\n\n\n", encodedString);
            free(encodedString);
        }
    }
    destroy_string(&input_str);
}

/*
 * command search
 */
void search() {
    String input_str = new_string();
    bool run = true;
    while(run) {
        printf("Enter character you want to translate (options '-o')\n(search) >> ");
        file_to_string(&input_str, stdin);
        if(strcmp(input_str.str, "-exit") == 0) {
            printf("Exiting search mode...\n");
            break;
        }
        else if(strcmp(input_str.str, "-o") == 0)
            printf("- '-exit' exit search mode\n");
        else {    
            char input_char = input_str.str[0];
            char morseCode[MAX_MORSE_CHAR_LENGTH];
            if(getMorseCode(input_char, morseCode) != 1)
                printf("this character was not found\n");
            else
                printf("\nMorse: %s\n\n\n", morseCode);
        }
    }
    destroy_string(&input_str);
}

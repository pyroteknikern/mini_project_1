#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdlib.h>
#include "morse.h"

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

void initializeDictionary() {
    // Initialize the dictionary with Morse code definitions
    // Implement this function to populate dictionary.characters and dictionary.morseCodes arrays.
    dictionary.id = 0;
    dictionary.size = MAX_DICTIONARY_SIZE;
    char chars[MAX_DICTIONARY_SIZE] = "1234567890abcdefghijklmnopqrstuvwxyz";
    strcpy(dictionary.characters, chars);
    char *mc[MAX_DICTIONARY_SIZE] = {".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    memcpy(dictionary.morseCodes, mc, sizeof(mc));
}

void getMorseCode(const char character, char *morseChar){
  //Implement this function to get the code of a specific character
    strcpy(morseChar, "");
    for(int i = 0; i < coderDecoder.dictionary.size; i++) {
        if(coderDecoder.caseSensitive) {
            if(character == coderDecoder.dictionary.characters[i]) {
                strcpy(morseChar, coderDecoder.dictionary.morseCodes[i]);
                return;
            }
        }
        else {
            if(tolower(character) == coderDecoder.dictionary.characters[i]) {
                strcpy(morseChar, coderDecoder.dictionary.morseCodes[i]);
                return;
            }
        }
    }
}

void initializeCoderDecoder(){
    // Initialize the coder decoder with a dictionary
    coderDecoder.dictionary = dictionary;
    coderDecoder.caseSensitive = true;
    coderDecoder.currentDictionaryId = dictionary.id;
}

void encodeToMorse(const char *text, char *encodedText) {
    encodedText[0] = '\0';
    char morseChar[MAX_MORSE_LENGTH] = "";
    for(int i = 0; i < strlen(text); i++) {
        getMorseCode(text[i], morseChar);
        if(strlen(morseChar) == 0) continue;
        strcat(encodedText, morseChar);
        strcat(encodedText, " ");
    }
}

void getCharFromMorse(const char* morseChar, char* character) {
    for(int i = 0; i < coderDecoder.dictionary.size; i++) {
        if(strcmp(coderDecoder.dictionary.morseCodes[i], morseChar) == 0) {
            *character = coderDecoder.dictionary.characters[i];
            return;
        }
    }
}

void decodeFromMorse(const char *morseCode, char *decodedText) {
    // Implement Morse code decoding logic here
    char morseChar[MAX_MORSE_LENGTH] = "";
    char placeholderChar;
    for(int i = 0; i < strlen(morseCode) + 1; i++) {
        if(morseCode[i] == ' ' || morseCode[i] == '\0') {
            getCharFromMorse(morseChar, &placeholderChar);
            strncat(decodedText, &placeholderChar, 1);
            morseChar[0] = '\0';
            continue;
        }
        strncat(morseChar, &morseCode[i], 1);
    }
}

            
void printDictionary() {
    // Implement the function to display the Morse code table
    printf("Morse\tAlphabet\n");
    for(int i = 0; i < coderDecoder.dictionary.size; i++) {
        printf("%s\t%c\n", coderDecoder.dictionary.morseCodes[i], coderDecoder.dictionary.characters[i]);
    }
}

void setMode(bool caseSensitive) {
    // Implement this function to set the case sensitivity mode
    coderDecoder.caseSensitive = caseSensitive;
}

void getPerfectSizeString(char* str_ptr) {
    char ch;
    while((ch = getc(stdin)) != EOF) {
        printf("%c\n", ch);
    }
}


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


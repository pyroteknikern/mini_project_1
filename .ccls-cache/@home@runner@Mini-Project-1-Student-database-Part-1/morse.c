#include <stdio.h>
#include <string.h>
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
}

void getMorseCode(const char character, char *morseCode){
  //Implement this function to get the code of a specific character
}

void initializeCoderDecoder(){
    // Initialize the coder decoder with a dictionary
}

void encodeToMorse(const char *text, char *encodedText) {
    // Implement Morse code encoding logic here
}

void decodeFromMorse(const char *morseCode, char *decodedText) {
    // Implement Morse code decoding logic here
}

void printDictionary() {
    // Implement the function to display the Morse code table
}

void setMode(bool caseSensitive) {
    // Implement this function to set the case sensitivity mode
}
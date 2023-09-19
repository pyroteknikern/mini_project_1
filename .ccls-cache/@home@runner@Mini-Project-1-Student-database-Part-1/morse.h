#ifndef MORSE_H
#define MORSE_H
#define MAX_CHAR_FNAME 32
#define MAX_CHAR_LNAME 64
#include "stdbool.h"

#define FALSE 0
#define TRUE 1

  // Define the maximum length for Morse code representation
#define MAX_MORSE_LENGTH 10

  // Define the maximum size of the Morse code dictionary
#define MAX_DICTIONARY_SIZE 36


// Define a structure for the Morse code dictionary
struct Dictionary {
    int id;
    char characters[MAX_DICTIONARY_SIZE];
    const char *morseCodes[MAX_DICTIONARY_SIZE];
};

typedef struct Dictionary Dictionary;

// Define a structure for the coder-decoder
struct CoderDecoder {
    Dictionary dictionary;
    int currentDictionaryId;
    bool caseSensitive;
};

typedef struct CoderDecoder CoderDecoder;


void displayHelp();

void initializeDictionary();

void getMorseCode(const char character, char *morseCode);

void printDictionary();

void initializeCoderDecoder();

void encodeToMorse(const char *text, char *encodedText);

void decodeFromMorse(const char *morseCode, char *decodedText);

void setMode(bool caseSensitive);

#endif
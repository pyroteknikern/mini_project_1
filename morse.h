#ifndef MORSE_H
#define MORSE_H
#include "stdbool.h"
#include<stdio.h>
#define FALSE 0
#define TRUE 1

  // Define the maximum length for Morse code representation
#define MAX_MORSE_CHAR_LENGTH 5

  // Define the maximum size of the Morse code dictionary
#define MAX_DICTIONARY_SIZE 36

#define CMD_SIZE 32

// Define a structure for the Morse code dictionary
struct Dictionary {
    int id;
    unsigned int size;
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
void decode();
void encode();
void search();
void printDictionary();
void setMode(bool caseSensitive);
void test();

void initializeDictionary();
int getMorseCode(const char character, char *morseCode);
void initializeCoderDecoder();
int encodeToMorse(const char *text, char *encodedText);
int decodeFromMorse(const char *morseCode, char *decodedText);
size_t nr_of_seg(char* , char );
void encode_file_to_file(FILE*, FILE*);
#endif

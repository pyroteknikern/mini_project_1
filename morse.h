#ifndef MORSE_H
#define MORSE_H
#include "stdbool.h"
#include<stdio.h>
#define FALSE 0
#define TRUE 1

#define uint unsigned int
  // Define the maximum length for Morse code representation
#define MAX_MORSE_CHAR_LENGTH 5
  // Define the maximum size of the Morse code dictionary
#define MAX_DICTIONARY_SIZE 36
#define CMD_SIZE 32

#define NR_OF_NUMBERS 10
#define NR_OF_CHARACTERS 26
// Define a structure for the Morse code dictionary
struct Dictionary {
    int id;
    uint size;
    char numbers[NR_OF_NUMBERS];
    char alphabet[NR_OF_CHARACTERS];
    char* morse_numbers[NR_OF_NUMBERS];
    char* morse_alphabet[NR_OF_CHARACTERS];

    char characters[MAX_DICTIONARY_SIZE];
    const char *morse_codes[MAX_DICTIONARY_SIZE];
};
typedef struct Dictionary Dictionary;

struct CoderDecoder {
    Dictionary dictionary;
    int current_dictionary_id;
    bool case_sensitive;
};
typedef struct CoderDecoder CoderDecoder;

void display_help();
void decode(CoderDecoder*);
void encode(CoderDecoder*);
void search(CoderDecoder*);
void print_dictionary(CoderDecoder*);
void set_mode(CoderDecoder*, bool caseSensitive);
void test();
void caesar(CoderDecoder*);
void status(CoderDecoder*);

Dictionary initialize_dictionary();
CoderDecoder initialize_coder_decoder(Dictionary*);
#endif

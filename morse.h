#ifndef MORSE_H
#define MORSE_H
#include "stdbool.h"
#include<stdio.h>
#define FALSE 0
#define TRUE 1

#define uint unsigned int
  // Define the maximum length for Morse code representation
#define MAX_MORSE_CHAR_LENGTH 6
  // Define the maximum size of the Morse code dictionary
#define MAX_DICTIONARY_SIZE 37 //space icluded
#define CMD_SIZE 32

#define NR_OF_NUMBERS 10
#define NR_OF_CHARACTERS 26
// Define a structure for the Morse code dictionary
struct Dictionary {
    uint id;
    uint size;
    char numbers[NR_OF_NUMBERS + 1];
    char alphabet[NR_OF_CHARACTERS + 1];
    char morse_numbers[NR_OF_NUMBERS][MAX_MORSE_CHAR_LENGTH + 1];
    char morse_alphabet[NR_OF_CHARACTERS][MAX_MORSE_CHAR_LENGTH + 1];

    char characters[MAX_DICTIONARY_SIZE + 1];
    char morse_codes[MAX_DICTIONARY_SIZE][MAX_MORSE_CHAR_LENGTH + 1];
};
typedef struct Dictionary Dictionary;

struct CoderDecoder {
    Dictionary dictionary;
    int current_dictionary_id;
    bool case_sensitive;
};
typedef struct CoderDecoder CoderDecoder;

void display_help();
void decode(const CoderDecoder*);
void encode(const CoderDecoder*);
void encode_file(const CoderDecoder*);
void search(const CoderDecoder*);
void print_dictionary(const CoderDecoder*);
void set_mode(CoderDecoder*, bool caseSensitive);
void test();
void caesar(const CoderDecoder*);
void status(const CoderDecoder*);

Dictionary initialize_dictionary();
CoderDecoder initialize_coder_decoder(Dictionary*);
#endif

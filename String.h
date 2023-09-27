#ifndef STRING_H
#define STRING_H
#include <stdio.h>
struct custom_string_type {
    size_t allocated_size;
    size_t length;
    char* str;
};

typedef struct custom_string_type String;

String new_string();
int char_append_string(String*, char);
int populate_string(String*, char*);
int cat_string(String*, String*);
void destroy_string(String*);
void file_to_string(String*, FILE*);
void print_string(String*);
int strendswith(char*, char);
int endswith_string(String*, char);
void trunk_trailing_spaces(char*);
#endif

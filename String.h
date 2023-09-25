#ifndef STRING_H
#define STRING_H
#include <stdio.h>
struct custom_string_type {
    size_t allocated_size;
    size_t length;
    size_t true_length;
    char* str;
};

typedef struct custom_string_type String;

String new_str();
int char_append_string(String*, char);
int populate_string(String*, char*);
int cat_string(String*, String*);
void destroy_string(String*);
void file_to_string(String*, FILE*);
void print_string(String*);

#endif

#ifndef STRING_H
#define STRING_H
#include <stdio.h>

struct custom_string_type {
    size_t allocated_size;
    size_t length;
    char* str;
};

typedef struct custom_string_type String;


String string_new();
int string_append_char(String*, char);
int string_populate(String*, char*);
int string_cat(String*, String*);
void string_destroy(String*);
void string_read_file(String*, FILE*);
void string_print(String*);
int string_endswith(String*, char);
void string_clear(String*);
void string_trunk_trailing_spaces(String*);


void str_trunk_trailing_spaces(char*);
int str_endswith(char*, char);


#endif

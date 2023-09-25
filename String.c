#include "String.h"
#include <string.h>
#include <stdlib.h>

String new_str() {
    String str;
    str.allocated_size = sizeof(char);
    str.str = malloc(sizeof(char));
    str.str[0] = '\0';
    str.length = 0;
    str.true_length = 1;
    return str;
}

int last_is_null(String* str) {
    if(str->str[str->true_length - 1] != '\0') return 0;
    return 1;
}

int char_append_string(String* str, char element) {
    if(str->true_length * sizeof(char) == str->allocated_size) {
        str->str = realloc(str->str, str->allocated_size * 2);
        str->allocated_size *= 2;
    }
    str->str[str->length] = element;
    str->str[str->true_length] = '\0';
    str->length++;
    str->true_length++;
    if(!last_is_null(str)) return -1;
    return 1;
}

int populate_string(String* str, char* cstring) {
    size_t len = strlen(cstring);
    size_t al_siz = (len  + 1) * sizeof(char);
    str->str = realloc(str->str, al_siz);
    str->allocated_size = al_siz;
    str->length = len;
    str->true_length = len + 1;

    for(int i = 0; i < len + 1; i++) {
        str->str[i] = cstring[i];
    }
    if(!last_is_null(str)) return -1;
    return 1;
}

int cat_string(String* dest, String* source) {
    size_t al_siz = (dest->length + source->length + 1) * sizeof(char);
    dest->str = realloc(dest->str, al_siz);
    dest->allocated_size = al_siz;
    for(int i = 0; i < source->true_length; i++) {
        dest->str[dest->length + i] = source->str[i];
    }
    dest->length += source->length;
    dest->true_length = dest->length + 1;
    if(!last_is_null(dest)) return -1;
    return 1;
}

void print_string(String* str) {
    for(int i = 0; i < str->length; i++) {
        printf("%c", str->str[i]);
    }
}

void file_to_string(String* str, FILE* file) {
    char ch;
    if(file == stdin) {
        while((ch = getc(file)) != '\n') {
            char_append_string(str, ch);
        }
    }
    else {
        while((ch = getc(file)) != EOF) {
            char_append_string(str, ch);
        }
    }
}

void destroy_string(String* str) {
    free(str->str);
}

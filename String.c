#include "String.h"
#include <string.h>
#include <stdlib.h>

/*
 * create dynamic string
 * return: dynamic string struct
 * note: before dynamic string goes out of scope call destroy_string(), if dynamic is not destroyed program will leak memory
 */
String new_str() {
    String str;
    str.allocated_size = sizeof(char);
    str.str = malloc(sizeof(char));
    str.str[0] = '\0';
    str.length = 0;
    str.true_length = 1;
    return str;
}

/*
 * check if last character is the nullbyte
 * param1: dynamic string you want to check
 * return: returns status, 1 if last is nullbyte, 0 if not
 * note: the last byte in the string should be the nullbyte so it can be used with normal string.h funcs
 */
int last_is_null(String* str) {
    if(str->str[str->true_length - 1] != '\0') return 0;
    return 1;
}

/*
 * append character to end of dynamic string
 * param1: dynamic string to append to
 * param2: character to append
 * return: returns status, 1 for success, -1 for failure
 */
int char_append_string(String* str, char element) {
    if(str->true_length * sizeof(char) == str->allocated_size) {
        str->str = realloc(str->str, str->allocated_size * 2);
        if(str->str == NULL) return -1;
        str->allocated_size *= 2;
    }
    str->str[str->length] = element;
    str->str[str->true_length] = '\0';
    str->length++;
    str->true_length++;
    if(!last_is_null(str)) return -1;
    return 1;
}

/*
 * populates dynamic string with cstring
 * param1: dynamic string to populate
 * param2: pointer to c-style string
 * return: return status, -1 for failure, 1 for success
 */
int populate_string(String* str, char* cstring) {
    size_t len = strlen(cstring);
    size_t al_siz = (len  + 1) * sizeof(char);
    str->str = realloc(str->str, al_siz);
    if(str->str == NULL) return -1;
    str->allocated_size = al_siz;
    str->length = len;
    str->true_length = len + 1;

    for(int i = 0; i < len + 1; i++) {
        str->str[i] = cstring[i];
    }
    if(!last_is_null(str)) return -1;
    return 1;
}

/*
 * concatenate dynamic strings
 * param1: destination
 * param2: source
 * return: returns status, -1 for failure, 1 for success
 */
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

/*
 * prints dynamic string
 * param1: dynamic string
 */
void print_string(String* str) {
    for(int i = 0; i < str->length; i++) {
        printf("%c", str->str[i]);
    }
}

/*
 * reads file and inserts text into dynamic string
 * param1: dynamic string
 * param2: file to read from
 */
void file_to_string(String* str, FILE* file) {
    char ch;
    str->length = 0;
    str->true_length = 1;
    str->str = malloc(sizeof(char));
    str->allocated_size = sizeof(char);
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

int strendswith(char* str, char ch) {
    size_t len = strlen(str);
    if(str[len] == ch) return 1;
    return 0;
}

int endswith_string(String* str, char ch) {
    if(str->str[str->length - 1] == ch) return 1;
    return 0;
}

void trunk_trailing_spaces(char* str) {
    for(int i = strlen(str) - 1; i >= 0; i--) {
        if(str[i] != ' ') return;
        str[i] = '\0';
    }
}

/*
 * destroys string
 * param1: dynamic string to destroy
 */
void destroy_string(String* str) {
    free(str->str);
}
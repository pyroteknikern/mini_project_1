#include "String.h"
#include <string.h>
#include <stdlib.h>

/*
 * trim excess memory of dynamic string
 * param1: dynamic string to resize
 */
void trim_mem(String* str) {
    size_t new_size = (str->length + 1) * sizeof(char);
    str->str = realloc(str->str, new_size);
    str->allocated_size = new_size;
}
/*
 * check if last character is the nullbyte
 * param1: dynamic string you want to check
 * return: returns status, 1 if last is nullbyte, 0 if not
 * note: the last byte in the string should be the nullbyte so it can be used with normal string.h funcs
 */
int last_is_null(String* str) {
    if(str->str[str->length] != '\0') return 0;
    return 1;
}

int str_endswith(char* str, char ch) {
    size_t len = strlen(str);
    if(str[len] == ch) return 1;
    return 0;
}

/*
 * removes trailing spaces from char[]
 * param1: char[] to remove trailing spaces from
 */
void str_trunk_trailing_spaces(char* str) {
    for(int i = strlen(str) - 1; i >= 0; i--) {
        if(str[i] != ' ') return;
        str[i] = '\0';
        printf("trunk\n");
    }
}

void string_trunk_trailing_spaces(String* str) {
    for(int i = str->length - 1; i >= 0; i--) {
        if(str->str[i] != ' ') return;
        str->length--;
        str->str[i] = '\0';
    }
    trim_mem(str); 
}


/*
 * create dynamic string
 * return: dynamic string struct
 * note: before dynamic string goes out of scope call destroy_string(), if dynamic is not destroyed program will leak memory
 */
String string_new() {
    String str;
    str.allocated_size = sizeof(char);
    str.str = malloc(sizeof(char));
    str.str[0] = '\0';
    str.length = 0;
    return str;
}


/*
 * append character to end of dynamic string
 * param1: dynamic string to append to
 * param2: character to append
 * return: returns status, 1 for success, -1 for failure
 */
int string_append_char(String* str, char element) {
    size_t str_length = str->length;
    size_t str_alloc = str->allocated_size;
    if(str_length + 1 * sizeof(char) == str_alloc) {
        str->str = realloc(str->str, str_alloc * 2);
        str->allocated_size = str_alloc * 2;
        if(str->str == NULL) {
            return -1;
        }
    }
    str->str[str_length] = element;
    str->str[str_length + 1] = '\0';
    str->length++;
    if(!last_is_null(str)) return -1;
    return 1;
}


/*
 * populates dynamic string with cstring
 * param1: dynamic string to populate
 * param2: pointer to c-style string
 * return: return status, -1 for failure, 1 for success
 */
int string_populate(String* str, char* cstring) {
    size_t len = strlen(cstring);
    size_t new_size = (len  + 1) * sizeof(char);
    str->str = realloc(str->str, new_size);
    str->allocated_size = new_size;
    if(str->str == NULL) return -1;
    str->length = len;

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
int string_cat(String* dest, String* source) {
    size_t new_size = (dest->length + source->length + 1) * sizeof(char);
    dest->str = realloc(dest->str, new_size);
    dest->allocated_size = new_size;
    for(int i = 0; i < source->length + 1; i++) {
        dest->str[dest->length + i] = source->str[i];
    }
    dest->length += source->length;
    if(!last_is_null(dest)) return -1;
    return 1;
}

/*
 * prints dynamic string
 * param1: dynamic string
 */
void string_print(String* str) {
    for(int i = 0; i < str->length; i++) {
        printf("%c", str->str[i]);
    }
}

/*
 * reads file and inserts text into dynamic string
 * param1: dynamic string
 * param2: file to read from
 */
void string_read_file(String* str, FILE* file) {
    char ch;
    //make sure that string is only nullbyte
    str->length = 0;
    str->str[0] = '\0';
    size_t pre_alloc_size = 256; // pre allocate memory for 255 + \0 characters to improve performance
    str->str = realloc(str->str, pre_alloc_size);
    str->allocated_size = pre_alloc_size;
    if(file == stdin) {
        while((ch = getc(file)) != '\n') {
            string_append_char(str, ch);
        }
    }
    else {
        while((ch = getc(file)) != EOF) {
            string_append_char(str, ch);
        }
    }
    trim_mem(str);
}

int string_endswith(String* str, char ch) {
    if(str->str[str->length - 1] == ch) return 1;
    return 0;
}


/*
 * clears content of dynamic string
 * param1: dynamic string to clear
 */
void string_clear(String* str) {
    str->str[0] = '\0';
    str->length = 0;
    trim_mem(str);
}
/*
 * destroys string
 * param1: dynamic string to destroy
 */
void string_destroy(String* str) {
    free(str->str);
}

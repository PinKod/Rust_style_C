//
// Created by Calamari Yeste on 2024-06-27.
//
#include "../include_headers/n_std_String.h"
#include "../include_headers//n_std_result.h"

#include "stdlib.h"
#include "string.h"


//function from_String create String from C null terminated string
//error codes for from_String:
//1 allocation fail
Result from_String(char *str) {
    Result result;
    String *string = malloc(sizeof (string));
    if(string == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    unsigned long long int str_len = strlen(str);
    unsigned long long int s_s_c = str_len + START_STRING_CAPACITY;
    string->ptr_to_first_char = malloc(sizeof (char) * s_s_c);
    if(string->ptr_to_first_char == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    string->length = str_len;
    string->capacity = s_s_c;
    string->ptr_to_first_char = memcpy(string->ptr_to_first_char, str, str_len / sizeof (char));
    result.res = Ok;
    result.ptr = string;
    return result;
}

#ifdef test1
int main() {
    char str[11] = "hello world";
    Result result = from_String(str);
    printf("res=%d\n", result.res);
    return 0;
}
#endif
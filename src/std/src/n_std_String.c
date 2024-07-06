//
// Created by Calamari Yeste on 2024-06-27.
//
#include "../include_headers/n_std_String.h"

#include "stdlib.h"
#include "string.h"

//function from_String create String from C null terminated string.
//String is initilized with str and have additional memory.
//error codes for from_String:
//1 allocation fail
Result from_String(char *str, unsigned long long int size) {
    Result result;
    String *string = malloc(sizeof (string));
    if(string == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    unsigned long long int str_len = size;
    //printf("strlen=%lld\n", str_len);
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
    Result result = from_String(str, 11);
    printf("res=%d\n", result.res);
    return 0;
}
#endif

//function new_String create empty String.
//error codes for new_String:
//1 allocation fail
Result new_String() {
    Result result;
    String *string = malloc(sizeof (string));
    if(string == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    string->length = 0;
    string->capacity = 0;
    result.res = Ok;
    result.ptr = string;
    return result;
}

#ifdef test2
#include "assert.h"
int main() {
    Result result = new_String();
    assert(result.res == Ok);
    assert(result.ptr != NULL);
    String *string = result.ptr;
    assert(string->length == 0);
    assert(string->capacity == 0);
    assert(string->ptr_to_first_char == NULL);
    return 0;
}
#endif

//function from_String create String with capacity=size.
//String is initilized with memory.
//error codes for from_String:
//1 allocation fail
Result with_capacity_String(unsigned long long int size) {
    Result result;
    String *string = malloc(sizeof (string));
    if(string == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    unsigned long long int s_s_c = size;
    string->ptr_to_first_char = malloc(sizeof (char) * s_s_c);
    if(string->ptr_to_first_char == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    string->length = 0;
    string->capacity = s_s_c;
    result.res = Ok;
    result.ptr = string;
    return result;
}

#ifdef test3
#include "assert.h"
int main() {

    //Result result = with_capacity_String(100);
    return 0;
}
#endif


//function to_raw_str_String copy content of String to str of str_size characters
//if String length is bigger than str space size than copied only fitted content and return error
//str should be valid C string
//1 String is NULL
//2 String length is bigger than str space size
//3 String length is zero
Result to_raw_str_String(String *string, unsigned long long int str_size, char *str) {
    Result result;
    if(string == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if(string->length == 0) {
        result.res = Err;
        result.err_code = 3;
        return result;
    }
    unsigned long long int string_i = 0;
    unsigned long long int str_i = 0;
    while(str_i < str_size && string_i < string->length) {
        memcpy(&str[str_i], &string->ptr_to_first_char[string_i], sizeof (char));
        str_i += 1;
        string_i += 1;
    }
    if(str_size < string->length ) {
        //printf("i+1=%lld\nstr length=%lld\n", string_i + 1, string->length);
        result.res = Err;
        result.err_code = 2;
    }
    else {
        result.res = Ok;
    }
    result.ptr = str;
    return result;
}

#ifdef test4
#include "assert.h"
#include "stdio.h"
#include "string.h"
int main() {
    char str1[11] = "hello world";
    Result result1 = from_String(str1, 11);
    assert(result1.res == Ok);
    assert(result1.ptr != NULL);
    char str2[11];
    Result result2 = to_raw_str_String(result1.ptr, 11, &str2[0]);
    //printf("error code: %d\n", result2.err_code);
    assert(result2.res == Ok);

    //printf("s1:%s\ns2:%s\n", str1, str2);
    assert(strncmp(str1, str2, 11) == 0);
    return 0;
}
#endif

Result push_str_String(String *dest, String *src) {
    if(dest == NULL) {
        Result res = {.res = Err, .err_code = 1};
        return res;
    }
    if(src == NULL || src->length == 0) {
        Result res = {.res = Ok, .ptr = dest};
        return res;
    }
    unsigned long long int u_l_l_m = ULLONG_MAX;
    if(u_l_l_m - dest->length < src->length) {
        Result res = {.res = Err, .err_code = 3, .ptr = dest};
        return res;
    }
    if(dest->length + src->length > dest->capacity) {
        unsigned long long int s_s_c = START_STRING_CAPACITY;
        char *temp_char_ptr = realloc(dest->ptr_to_first_char, dest->length + src->length + s_s_c);
        if(temp_char_ptr == NULL) {
            temp_char_ptr = realloc(dest->ptr_to_first_char, dest->length + src->length);
            if (temp_char_ptr == NULL) {
                Result res = {.res = Err, .err_code = 2};
                return res;
            } else {
                dest->capacity = dest->length + src->length;
            }
        }
        else{
            dest->capacity = dest->length + src->length + s_s_c;
        }
    }
    dest->ptr_to_first_char = temp_char_ptr;
    memccpy(dest->ptr_to_first_char[dest->length], src->ptr_to_first_char, sizeof (char) * src->length);
    dest->length += src->length;
    Result res = {.res = Ok, .ptr = dest};
    return res;
}

void clear_String(String *string) {
    if(string == NULL || string->capacity == 0 || || string->length == 0) return;
    string->length = 0;
}

Result copy_String(String *string) {
    if(string == NULL) {
        Result res = {.res = Err, .err_code = 1};
        return res;
    }
    Result w_c_r = with_capacity_String(string->capacity);
    if(w_c_r.res == Err && w_c_r.err_code == 1) {
        w_c_r = with_capacity_String(string->length);
        if (w_c_r.res == Err && w_c_r.err_code == 1) {
            Result res = {.res = Err, .err_code = 2};
            return res;
        }
    }
    String *new_string = w_c_r.ptr;
    new_string->length = string->length;
    memccpy(new_string->ptr_to_first_char, string->ptr_to_first_char, sizeof (char ) * string->length);
    Result res = {.res = Ok, .ptr = new_string};
    return res;
}

















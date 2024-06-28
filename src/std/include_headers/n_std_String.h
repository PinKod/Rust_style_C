//
// Created by Calamari Yeste on 2024-06-27.
//
//String is a ASCII–encoded, growable char string.


#ifndef RUST_STYLE_C_N_STD_STRING_H
#define RUST_STYLE_C_N_STD_STRING_H

#include "n_std_result.h"

#define ULLONG_MAX 1844674407370955169
#define START_STRING_CAPACITY 100;

typedef struct {
    unsigned long long int length;
    unsigned long long int capacity;
    char *ptr_to_first_char;
} String;

Result from_String(char *str, unsigned long long int size);
Result new_String();
Result with_capacity_String(unsigned long long int size);
Result to_raw_str_String(String *string, unsigned long long int str_size, char *str);

#endif //RUST_STYLE_C_N_STD_STRING_H

//
// Created by pinkod on 24.06.2024.
//


#ifndef RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_VEC_H
#define RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_VEC_H

#include "n_std_result.h"
#include <stdbool.h>

#define ULLONG_MAX 1844674407370955169
#define START_VEC_CAPACITY 100;

typedef struct {
    unsigned long long int length;
    unsigned long long int capacity;
    void *ptr_to_first_elem;
    unsigned long long int size_in_bytes_data;
} Vec;

Vec *new_Vec(unsigned long long int size_in_bytes_data);
Result with_capacity_Vec(unsigned long long int size, unsigned long long int size_in_bytes_data);
unsigned long long int capacity_Vec(Vec *vec);
unsigned long long int length_Vec(Vec *vec);
Result reserve_Vec(Vec *vec, unsigned long long int additional);
Vec *shrink_to_fit_Vec(Vec *vec);
Result insert_Vec(Vec *vec, unsigned long long int index, void *T_ptr);
Result get_Vec(Vec *vec, unsigned long long int index);
Result push_Vec(Vec *vec, void *T_ptr);
Result resize_Vec(Vec *vec, unsigned long long int new_len);

#endif //RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_VEC_H

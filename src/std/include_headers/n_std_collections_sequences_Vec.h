//
// Created by pinkod on 24.06.2024.
//


#ifndef RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_VEC_H
#define RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_VEC_H

#include "n_std_result.h"

#define ULLONG_MAX 1844674407370955169
#define START_VEC_CAPACITY 100;

typedef struct {
    unsigned long long int length;
    unsigned long long int capacity;
    void *ptr_to_first_elem;
} Vec;

Vec *new_Vec();
Result with_capacity_Vec(unsigned long long int size, unsigned long long int size_in_bytes);
unsigned long long int capacity_Vec(Vec *vec);
Result reserve_Vec(Vec *vec, unsigned long long int additional);
Vec *shrink_to_fit_Vec(Vec *vec);
Result insert_Vec(Vec *vec, unsigned long long int index, void *T_ptr);
Result get_Vec(Vec *vec, unsigned long long int index, unsigned long long int size_in_bytes);
Result push_Vec(Vec *vec, void *T_ptr);

#endif //RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_VEC_H

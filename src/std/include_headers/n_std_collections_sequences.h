//
// Created by pinkod on 24.06.2024.
//


#ifndef RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_H
#define RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_H

#include "n_std_collections_sequences_Vec.h"

#include "stdbool.h"

typedef struct {
    bool valid;
    unsigned long long int current_size;
    void *const ptr_to_first_elem;
} LinkedList;


#endif //RUST_STYLE_C_N_STD_COLLECTIONS_SEQUENCES_H

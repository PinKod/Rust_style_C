//
// Created by Calamari Yeste on 2024-07-06.
//

#ifndef RUST_STYLE_C_N_STD_MEMORY_MANAGER_H
#define RUST_STYLE_C_N_STD_MEMORY_MANAGER_H

#include "n_std_collections_sequences_Vec.h"

typedef struct {
    Vec *vec;
} Memory_Manager;

Memory_Manager memory_manager_init();

#endif //RUST_STYLE_C_N_STD_MEMORY_MANAGER_H

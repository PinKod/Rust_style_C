//
// Created by Calamari Yeste on 2024-07-06.
//
#include "stdio.h"
#include "../std/include_headers/n_std_memory_manager.h"
#include "assert.h"

extern Memory_Manager global_memory_manager;

void test() {
    printf("test2\n");
    assert(global_memory_manager.vec != NULL);
    assert(global_memory_manager.vec->ptr_to_first_elem != NULL);
    assert(global_memory_manager.vec->length  == 0);
    assert(global_memory_manager.vec->capacity == 100);
}
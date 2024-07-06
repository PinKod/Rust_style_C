//
// Created by Calamari Yeste on 2024-07-06.
//

#include "../include_headers/n_std_memory_manager.h"
#include "stdlib.h"

Memory_Manager memory_manager_new() {
    Memory_Manager  memory_manager;
    Vec *vec = malloc(sizeof (Vec));
    if(vec != NULL) {
        vec->length = 0;
        unsigned long long int size = 100;
        unsigned long long int size_in_bytes_data = sizeof(void*);
        vec->ptr_to_first_elem = malloc(size_in_bytes_data * size);
        if(vec->ptr_to_first_elem == NULL) {
            exit(1);
        }
        else {
            vec->capacity = size;
        }
    }
    else {
        exit(1);
    }
    vec->size_in_bytes_data = sizeof(void*);
    vec->free_item_function_ptr = NULL;
    memory_manager.vec = vec;
    return memory_manager;
}

#ifdef test1
#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "../include_headers/n_std_memory_manager.h"
#include "../include_headers/global_variables.h"

int main() {
    global_memory_manager = memory_manager_new();
    assert(global_memory_manager.vec != NULL);
    assert(global_memory_manager.vec->ptr_to_first_elem != NULL);
    assert(global_memory_manager.vec->length  == 0);
    assert(global_memory_manager.vec->capacity   ==  100);
    return 0;
}
#endif


#include "stdio.h"
#include "../std/include_headers/n_std_memory_manager.h"
#include "assert.h"

Memory_Manager global_memory_manager;

void test();

int main() {
    global_memory_manager = memory_manager_new();
    assert(global_memory_manager.vec != NULL);
    assert(global_memory_manager.vec->ptr_to_first_elem != NULL);
    assert(global_memory_manager.vec->length  == 0);
    assert(global_memory_manager.vec->capacity   ==  100);
    test();
    return 0;
}
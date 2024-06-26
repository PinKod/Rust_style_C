//
// Created by pinkod on 24.06.2024.
//
#include "./../include_headers/n_std_collections_sequences_Vec.h"



#include "stdlib.h"
#include "string.h"

Result resize_Vec(Vec *vec);

Vec *new_Vec(){
    Vec *vec = malloc(sizeof (Vec));
    if(vec != NULL) {
        vec->length = 0;
        vec->capacity = 0;
        vec->ptr_to_first_elem = NULL;
    }
    return vec;
}


//error codes function with_capacity_Vec:
//1 allocation error
Result with_capacity_Vec(unsigned long long int size, unsigned long long int size_in_bytes) {
    Vec *vec = malloc(sizeof (Vec));
    Result result;
    if(vec != NULL) {
        vec->length = 0;
        if(size == 0) {
            vec->capacity = 0;
            vec->ptr_to_first_elem = NULL;
            result.res = Ok;
        }
        else {
            vec->ptr_to_first_elem = malloc(size_in_bytes * size);
            if(vec->ptr_to_first_elem == NULL) {
                free(vec);
                result.res = Err;
                result.err_code = 1;
            }
            else {
                vec->capacity = size;
                result.res = Ok;
            }
        };
    }
    else {
        result.res = Err;
        result.err_code = 1;
    }
    result.ptr = vec;
    return result;
}

unsigned long long int capacity_Vec(Vec *vec) {
    if(vec != NULL) return vec->capacity;
    return 0;
}

//error codes function with_capacity_Vec:
//1 allocation error
//2 exceeded limit of unsigned long long int
//3 vec is NULL
Result reserve_Vec(Vec *vec, unsigned long long int additional) {
    Result result;
    result.ptr = vec;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 3;
        return result;
    }
    if(vec->capacity + additional > ULLONG_MAX) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    void *realloc_ptr = realloc(vec->ptr_to_first_elem, (vec->capacity + additional) * sizeof (*vec->ptr_to_first_elem));
    if(realloc_ptr == NULL){
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    else {
        vec->ptr_to_first_elem = realloc_ptr;
        result.res = Ok;
        result.ptr = vec;
    }
    return result;
}

Vec *shrink_to_fit_Vec(Vec *vec) {
    if(vec == NULL || vec->capacity == 0) return vec;
    vec->ptr_to_first_elem = realloc(vec->ptr_to_first_elem, vec->length * sizeof (*vec->ptr_to_first_elem));
    return vec;
}


//error codes function insert_Vec:
//1 vec is NULL
//2 index is greater than vec capacity
Result insert_Vec(Vec *vec, unsigned long long int index, void *T_ptr) {
    Result result;
    result.ptr = vec;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if( index > vec->capacity) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    result.res = Ok;
    void *ptr = vec->ptr_to_first_elem;
    ptr = (int*)((char*)ptr + (sizeof (T_ptr)) * index);
    memcpy(ptr, T_ptr, sizeof (*T_ptr));
    return result;
}


//error codes function insert_Vec:
//1 vec is NULL
//2 index is greater than vec length
Result get_Vec(Vec *vec, unsigned long long int index, unsigned long long int size_in_bytes) {
    Result result;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if(vec->length < index) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    result.res = Ok;
    void *ptr = vec->ptr_to_first_elem;
    ptr = (int*)((char*)ptr + size_in_bytes * index);
    result.ptr = ptr;
    return result;
}

//error codes function insert_Vec:
//1 vec is NULL
//2 index is greater than vec length
Result push_Vec(Vec *vec, void *T_ptr) {
    Result result;
    result.ptr = vec;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }

    return res;
}

//error codes function insert_Vec:
//1 vec is NULL
//2 index is greater than vec length
Result resize_Vec(Vec *vec) {

}






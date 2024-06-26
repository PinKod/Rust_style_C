//
// Created by pinkod on 24.06.2024.
//
#include "./../include_headers/n_std_collections_sequences_Vec.h"



#include "stdlib.h"
#include "string.h"



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
        vec->capacity += additional;
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
//2 index is greater than vec length
Result insert_Vec(Vec *vec, unsigned long long int index, void *T_ptr) {
    Result result;
    result.ptr = vec;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if(index > vec->length) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    result.res = Ok;
    void *ptr = vec->ptr_to_first_elem;
    ptr = (void*)((char*)ptr + (sizeof (T_ptr)) * index);
    ptr = memcpy(ptr, T_ptr, sizeof (*T_ptr));
    return result;
}


//error codes function get_Vec:
//1 vec is NULL
//2 index is greater than vec length
Result get_Vec(Vec *vec, unsigned long long int index, unsigned long long int size_in_bytes_data) {
    Result result;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if(index > vec->length - 1) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    result.res = Ok;
    void *ptr = vec->ptr_to_first_elem;
    ptr = (void*)((char*)ptr + size_in_bytes_data * index);
    result.ptr = ptr;
    return result;
}

//error codes function push_Vec:
//1 vec is NULL
//2 vec capacity is more than max size of usingned long long int of items
//3 allocation fail
Result push_Vec(Vec *vec, void *T_ptr, unsigned long long int size_in_bytes_data) {
    Result result;
    result.ptr = vec;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if(vec->capacity - vec->length == 0) {
        Result temp_result = resize_Vec(vec, vec->capacity);
        if(temp_result.res == Err) {
            result.res = Err;
            result.err_code = temp_result.err_code;
            return result;
        }
        vec = result.ptr;
    }
    void *ptr = vec->ptr_to_first_elem;
    ptr = (void*)((char*)ptr + size_in_bytes_data * (vec->length));
    ptr = memcpy(ptr, T_ptr, size_in_bytes_data);
    vec->length += 1;
    result.res = Ok;
    return result;
}

//error codes function insert_Vec:
//1 vec is NULL
//2 vec capacity is more than max size of usingned long long int of items
//3 allocation fail
Result resize_Vec(Vec *vec, unsigned long long int new_len) {
    Result result;
    result.ptr = vec;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    unsigned long long int additional;
    bool less_than_now = false;
    unsigned long long int s_v_c = START_VEC_CAPACITY;
    unsigned long long int u_u_l_m = ULLONG_MAX;
    if(vec->capacity == u_u_l_m) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    if(new_len == vec->capacity) {
        if(u_u_l_m - vec->capacity < s_v_c) {
            additional = u_u_l_m - vec->capacity;
        }
        else {
            additional = s_v_c;
        }
    }
    else if(new_len < vec->capacity) {
        less_than_now = true;
        additional = vec->capacity - new_len;
    }
    else {
        additional = new_len - vec->capacity;
    }
    void *temp_realloc_ptr = NULL;

    unsigned long long int temp_vec_capacity;
    if(less_than_now == true) temp_vec_capacity = vec->capacity - additional;
    else temp_vec_capacity = vec->capacity + additional; 

    if(less_than_now == true) temp_realloc_ptr = realloc(vec->ptr_to_first_elem , sizeof(*vec->ptr_to_first_elem) * (vec->capacity - additional));
    else temp_realloc_ptr = realloc(vec->ptr_to_first_elem , sizeof(*vec->ptr_to_first_elem) * (vec->capacity + additional));
    if (temp_realloc_ptr == NULL) {
        result.res = Err;
        result.err_code = 3;
        return result;
    }
    vec->capacity = temp_vec_capacity;
    vec->ptr_to_first_elem = temp_realloc_ptr;
    result.res = Ok;
    return result;
}






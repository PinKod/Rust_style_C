//
// Created by pinkod on 24.06.2024.
//
#include "./../include_headers/n_std_collections_sequences_Vec.h"

#include "stdlib.h"
#include "string.h"
#include "stdarg.h"

//note: function new_Vec returns NULL, than allocation failed
Vec *new_Vec(unsigned long long int size_in_bytes_data, void (*free_item_function_ptr)(void *ptr)){
    Vec *vec = malloc(sizeof (Vec));
    if(vec != NULL) {
        vec->length = 0;
        vec->capacity = 0;
        vec->ptr_to_first_elem = NULL;
        vec->size_in_bytes_data = size_in_bytes_data;
        vec->free_item_function_ptr = free_item_function_ptr;
    }
    return vec;
}

//error codes function with_capacity_Vec:
//1 allocation error
Result with_capacity_Vec(unsigned long long int size, unsigned long long int size_in_bytes_data, void (*free_item_function_ptr)(void *ptr)) {
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
            vec->ptr_to_first_elem = malloc(size_in_bytes_data * size);
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
    vec->size_in_bytes_data = size_in_bytes_data;
    vec->free_item_function_ptr = free_item_function_ptr;
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
    void *realloc_ptr = realloc(vec->ptr_to_first_elem, (vec->capacity + additional) * vec->size_in_bytes_data);
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
    vec->ptr_to_first_elem = realloc(vec->ptr_to_first_elem, vec->length * vec->size_in_bytes_data);
    return vec;
}

//error codes function insert_Vec:
//1 vec is NULL
//2 index is greater than vec length
//Note that this function can only insert values inside Vec length
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
    ptr = (void*)((char*)ptr + vec->size_in_bytes_data * index);
    ptr = memcpy(ptr, T_ptr, vec->size_in_bytes_data);
    return result;
}

//error codes function get_Vec:
//1 vec is NULL
//2 index is greater than vec length
Result get_Vec(Vec *vec, unsigned long long int index) {
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
    ptr = (void*)((char*)ptr + vec->size_in_bytes_data * index);
    result.ptr = ptr;
    return result;
}

//error codes function push_Vec:
//1 vec is NULL
//2 vec capacity is more than max size of usingned long long int of items
//3 allocation fail
Result push_Vec(Vec *vec, void *T_ptr) {
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
    ptr = (void*)((char*)ptr + vec->size_in_bytes_data * vec->length);
    ptr = memcpy(ptr, T_ptr, vec->size_in_bytes_data);
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

    if(less_than_now == true) temp_realloc_ptr = realloc(vec->ptr_to_first_elem , vec->size_in_bytes_data * (vec->capacity - additional));
    else temp_realloc_ptr = realloc(vec->ptr_to_first_elem , vec->size_in_bytes_data * (vec->capacity + additional));
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

unsigned long long int length_Vec(Vec *vec) {
    if(vec != NULL) return vec->length;
    return 0;
}

//Clears the Vec, removing all items
//Note that this function has no effect on the allocated capacity of the Vec
void clear_Vec(Vec *vec) {
    vec->length = 0;
}

//error codes function pop_Vec:
//1 vec is NULL
//2 vec is empty
//3 logical error, index is out of bounds
//!!!Warning!!! allocated memory for Vec POPed item, need to be manually free, on calling side
Result pop_Vec(Vec *vec) {
    Result result;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if(vec->length == 0) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    Result res_get = get_Vec(vec, vec->length - 1);
    if(res_get.res == Err) {
        result.res = Err;
        result.err_code = 3;
        return result;
    }
    result.res = Ok;
    result.ptr = res_get.ptr;
    vec->length -= 1;
    if(vec->capacity - vec->length >= 200) {
        unsigned long long int s_v_c = START_VEC_CAPACITY;
        vec->ptr_to_first_elem = realloc(vec->ptr_to_first_elem, vec->size_in_bytes_data * vec->capacity - s_v_c);
    }
    return result;
}

//error codes function swap:
//1 allocation failure
Result swap(unsigned long long int size_in_bytes_data, void* a, void* b) 
{ 
    void *temp_buffer = malloc(size_in_bytes_data);
    if(temp_buffer == NULL) {
        Result result = {.res = Err, .err_code= 1};
        return result;
    }
    temp_buffer = memcpy(temp_buffer, a, size_in_bytes_data);
    //printf("!swap!\n");
    a = memcpy(a, b, size_in_bytes_data); 
    b = memcpy(b , temp_buffer, size_in_bytes_data); 
    Result result = {.res = Ok};
    return result;
} 

//error codes function bubbleSort:
//1 get_Vec function return Err
//2 allocation failure, in swapping function
Result bubbleSort(Vec *vec, int n, bool (*func_comparison_ptr_if_first_bigger)(void *ptr1, void *ptr2)){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            //if (arr[j] > arr[j + 1]) {
            Result res_get_j = get_Vec(vec, j);
            Result res_get_j_plus_1 = get_Vec(vec, j + 1);    
            if(res_get_j.res == Err || res_get_j_plus_1.res == Err) {
                Result result = {.res = Err, .err_code=1};
                return result;
            }
            if(func_comparison_ptr_if_first_bigger(res_get_j.ptr, res_get_j_plus_1.ptr) == true) {
                Result res_swap = swap(vec->size_in_bytes_data, res_get_j.ptr, res_get_j_plus_1.ptr);
                if(res_swap.res == Err) {
                    Result result = {.res = Err, .err_code=2};
                    return result;
                }
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    Result result = {.res= Ok, .ptr=vec};
    return result;
}

//error codes function sort_Vec:
//1 vec is NULL
//2 vec is empty
//3 logical error, index is out of bounds
//4 sorting error 
//Note: sort_Vec is using bubble sort
Result sort_Vec(Vec *vec, bool (*func_comparison_ptr_if_first_bigger)(void *ptr1, void *ptr2)) {
    Result result;
    if(vec == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if(vec->length == 0) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    if(vec->length == 1) {
        result.res = Ok;
        result.ptr = vec;
        return result;
    }
    Result sort_res = bubbleSort(vec, vec->length, func_comparison_ptr_if_first_bigger);
    if(sort_res.res == Err) {
        result.res = Err;
        result.err_code = 4;
        return result;
    }
    result.res = Ok;
    result.ptr = vec;
    return result;
}


//Moves all the items of vec_src to vec_dest, leaving vec_src empty if drop == true
//error codes function append_Vec:
//1 vec_dest is NULL
//2 vec_src is NULL
//3 vec_src is empty
//4 allocation failed
//5 logical error
Result append_Vec(Vec *vec_dest, Vec *vec_src, ...) {
    Result result;
    if(vec_dest == NULL) {
        result.res = Err;
        result.err_code = 1;
        return result;
    }
    if(vec_src == NULL) {
        result.res = Err;
        result.err_code = 2;
        return result;
    }
    if(vec_src->length == 0) {
        result.res = Err;
        result.err_code = 3;
        return result;
    }
    reserve_Vec(vec_dest, vec_src->length);
    if(vec_dest->capacity - vec_dest->length < vec_src->length) {
        result.res = Err;
        result.err_code = 4;
        return result;  
    }
    for(unsigned long long int i = 0; i < vec_src->length; i++) {
        Result get_res = get_Vec(vec_src, i);
        if(get_res.res == Err) {
            result.res = Err;
            result.err_code = 5;
            return result;
        }
        Result res_push = push_Vec(vec_dest, get_res.ptr);
        if(res_push.res == Err) {
            result.res = Err;
            result.err_code = 4;
            return result;
        }
    }
    

    va_list factor;         //указатель va_list
    va_start(factor, vec_src);
    bool *drop = NULL;
    *drop = va_arg(factor, bool);
    va_end(factor);
    if(drop != NULL && drop == true) {
        if(vec_dest->free_item_function_ptr != NULL) {

        }
        free(vec_src->ptr_to_first_elem);
    }
    result.res = Ok;
    result.ptr = vec_dest;
    return result;
}












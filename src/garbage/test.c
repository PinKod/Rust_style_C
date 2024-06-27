//
// Created by pinkod on 20.06.2024.
//
#include "../std/include_headers/n_std.h"
#include <stdlib.h>

typedef struct {
    int i;
    double ii;
    char iii[100];
} foo;

bool if_bigger(void *a, void *b);

int main() {
    Vec *vec = new_Vec(sizeof(foo));

    
    for(int i = 0; i < 333; i++) {
        int val = rand();
        foo j = {.i= val, .ii = (double)(int)val * 0.0000001};
        sprintf(j.iii, "%d", i);
        Result res = push_Vec(vec, &j);
        if(res.res == Err) {
            printf("error code: %d\niteration: %d", res.err_code, i);
        }
    }

    for(int i = 0; i < (int)length_Vec(vec); i++) {
        Result res = get_Vec(vec, i);
        if(res.res == Err) continue;
        foo j = *(foo*)res.ptr;
        printf("%3d)    a=%3d    b=%3f    c=%s\n", i, j.i, j.ii, j.iii);
    }

    printf("\n\n\n\n\n");
    bool (*if_bigger_function_ptr)(void *ptr1, void *ptr2);
    if_bigger_function_ptr = if_bigger;
    Result sort_res = sort_Vec(vec, if_bigger_function_ptr);
    if(sort_res.res == Err) {

        printf("sort error\ncode: %d\n", sort_res.err_code);
        return 0;
    }

    for(int i = 0; i < 333; i++) {
        Result res = pop_Vec(vec);
        if(res.res == Err) {
            printf("error code: %d      iteration: %d\n", res.err_code, i);
        }
        else {
            foo f_s = *(foo*)res.ptr;
            printf("%3d)    a=%3d    b=%3f    c=%s\n", i, f_s.i, f_s.ii, f_s.iii);
        }
    }

    return 0;
}

bool if_bigger(void *a, void *b) {
    
    foo A = *(foo *)a;
    foo B = *(foo *)b;
    //printf("A.ii=%lf     B.ii=%lf",A.ii, B.ii);
    if(A.ii >= B.ii){
        //printf("    true\n");
        return true;
    } 
    else {
        //printf("    false\n");
        return false;
    }
}







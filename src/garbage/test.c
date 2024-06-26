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

int main() {
    Vec *vec = new_Vec(sizeof(foo));

    
    for(int i = 0; i < 333; i++) {
        foo j = {.i= i, .ii = 0.9 * i};
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
    return 0;
}

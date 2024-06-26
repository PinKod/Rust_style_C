//
// Created by pinkod on 20.06.2024.
//
#include "../std/include_headers/n_std.h"

struct foo {
    int a;
    double b;
    char c[10];
};

int main() {
    struct foo abc = {.a = 10, .b = 20.22, .c = "abcde12345"};
    Result result1 = with_capacity_Vec(10, sizeof(struct foo));
    Vec *vec = NULL;
    if(result1.res == Ok) vec = result1.ptr;
    insert_Vec(vec, 2, &abc);
    Result result2 = get_Vec(vec, 2, sizeof (struct foo));
    if(result2.res == Ok) {
        struct foo ABC = *(struct foo*)result2.ptr;
        printf("a=%d\nb=%f\nc=%s\n", ABC.a, ABC.b, ABC.c);
    }
    else printf("error code: %d\n", result2.err_code);
    return 0;
}
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
    printf("abc:\na=%d\nb=%f\nc=%s\n", abc.a, abc.b, abc.c);
    struct foo def = {.a = 99, .b = 44.55, .c = "defgh78910"};
    printf("def:\na=%d\nb=%f\nc=%s\n\n", def.a, def.b, def.c);
    //Result result1 = with_capacity_Vec(10, sizeof(struct foo));
    Vec *vec = new_Vec();
    Result push_res;
    push_res = push_Vec(vec, &abc, sizeof(struct foo));
    if(push_res.res == Ok) printf("Ok1\n");
    push_res = push_Vec(vec, &def, sizeof(struct foo));
    if(push_res.res == Ok) printf("Ok2\n");
    Result result2 = get_Vec(vec, 1, sizeof (struct foo));
    if(result2.res == Ok) {
        struct foo *ABC = (struct foo*)result2.ptr;
        printf("a=%d\nb=%f\nc=%s\n", ABC->a, ABC->b, ABC->c);
    }
    else printf("error code2: %d\n", result2.err_code);
    return 0;
}

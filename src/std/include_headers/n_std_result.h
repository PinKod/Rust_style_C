//
// Created by pinkod on 24.06.2024.
//



#ifndef RUST_STYLE_C_N_STD_RESULT_H
#define RUST_STYLE_C_N_STD_RESULT_H
#include "stdio.h"

typedef enum {
    Ok,
    Err
} ResultEnum;

typedef struct {
    ResultEnum res;
    void *ptr;
    int err_code;
} Result;

#endif //RUST_STYLE_C_N_STD_RESULT_H

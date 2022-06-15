#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} int2_t;

int2_t int2_create(const int32_t x, const int32_t y);
int2_t int2_create_both(const int32_t b);
int2_t int2_add(const int2_t a, const int2_t b);
int2_t int2_sub(const int2_t a, const int2_t b);
int2_t int2_mul(const int2_t a, const int2_t b);
int2_t int2_scale(const int2_t a, const float b);

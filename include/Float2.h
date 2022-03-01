#pragma once

#include <stdbool.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Float2;

Float2 Float2_add(const Float2 a, const Float2 b);
Float2 Float2_subtract(const Float2 a, const Float2 b);
Float2 Float2_multiply(const Float2 a, const float b);
Float2 Float2_multiplyVec(const Float2 a, const Float2 b);
Float2 Float2_divide(const Float2 a, const float b);
Float2 Float2_divideVec(const Float2 a, const Float2 b);
Float2 Float2_getNormalized(const Float2 vec);
float Float2_getMagnitudeSq(const Float2 vec);
float Float2_getMagnitude(const Float2 vec);

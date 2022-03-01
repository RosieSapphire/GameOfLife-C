#pragma once

#include <stdbool.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Int2;

Int2 Int2_add(const Int2 a, const Int2 b);
Int2 Int2_subtract(const Int2 a, const Int2 b);
Int2 Int2_multiply(const Int2 a, const int b);
Int2 Int2_multiplyVec(const Int2 a, const Int2 b);
Int2 Int2_divide(const Int2 a, const int b);
Int2 Int2_divideVec(const Int2 a, const Int2 b);
Int2 Int2_getNormalized(const Int2 vec);
int Int2_getMagnitudeSq(const Int2 vec);
float Int2_getMagnitude(const Int2 vec);
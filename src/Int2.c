#include "Int2.h"

Int2 Int2_add(const Int2 a, const Int2 b) {
    return (Int2){a.x + b.x, a.y + b.y};
}

Int2 Int2_subtract(const Int2 a, const Int2 b) {
    return (Int2){a.x - b.x, a.y - b.y};
}

Int2 Int2_multiply(const Int2 a, const int b) {
    return (Int2){a.x * b, a.y * b};
}

Int2 Int2_multiplyVec(const Int2 a, const Int2 b) {
    return (Int2){a.x * b.x, a.y * b.y};
}

Int2 Int2_divide(const Int2 a, const int b) {
    return (Int2){a.x / b, a.y / b};
}

Int2 Int2_divideVec(const Int2 a, const Int2 b) {
    return (Int2){a.x / b.x, a.y / b.y};
}

int Int2_getMagnitudeSq(const Int2 vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

float Int2_getMagnitude(const Int2 vec) {
    return sqrtf((float)Int2_getMagnitudeSq(vec));
}

Int2 Int2_getNormalized(const Int2 vec) {
    const float magnitude = Int2_getMagnitude(vec);
    return Int2_multiply(vec, (bool)((1.0f / magnitude) > 0.0f) ? magnitude : 1.0f);
}
#include "Float2.h"

Float2 Float2_add(const Float2 a, const Float2 b) {
    return (Float2){a.x + b.x, a.y + b.y};
}

Float2 Float2_subtract(const Float2 a, const Float2 b) {
    return (Float2){a.x - b.x, a.y - b.y};
}

Float2 Float2_multiply(const Float2 a, const float b) {
    return (Float2){a.x * b, a.y * b};
}

Float2 Float2_multiplyVec(const Float2 a, const Float2 b) {
    return (Float2){a.x * b.x, a.y * b.y};
}

Float2 Float2_divide(const Float2 a, const float b) {
    return (Float2){a.x / b, a.y / b};
}

Float2 Float2_divideVec(const Float2 a, const Float2 b) {
    return (Float2){a.x / b.x, a.y / b.y};
}

float Float2_getMagnitudeSq(const Float2 vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

float Float2_getMagnitude(const Float2 vec) {
    return sqrtf(Float2_getMagnitudeSq(vec));
}

Float2 Float2_getNormalized(const Float2 vec) {
    const float magnitude = Float2_getMagnitude(vec);
    return Float2_multiply(vec, (bool)((1.0f / magnitude) > 0.0f) ? magnitude : 1.0f);
}
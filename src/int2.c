#include "int2.h"

int2_t int2_create(const int32_t x, const int32_t y) {
	int2_t v;
	v.x = x;
	v.y = y;
	return v;
}

int2_t int2_create_both(const int32_t b) {
	int2_t v;
	v.x = b;
	v.y = b;
	return v;
}

int2_t int2_add(const int2_t a, const int2_t b) {
	int2_t v;
	v = a;
	v.x += b.x;
	v.y += b.y;
	return v;
}

int2_t int2_sub(const int2_t a, const int2_t b) {
	int2_t v;
	v = a;
	v.x -= b.x;
	v.y -= b.y;
	return v;
}

int2_t int2_multiply(const int2_t a, const int2_t b) {
	int2_t v;
	v = a;
	v.x *= b.x;
	v.y *= b.y;
	return v;
}

int2_t int2_scale(const int2_t a, const float b) {
	int2_t v;
	v = a;
	v.x *= b;
	v.y *= b;
	return v;
}

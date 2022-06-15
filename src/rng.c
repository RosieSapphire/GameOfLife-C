#include "RNG.h"

void RNG_initialize(RNG* rng, const unsigned short seed) {
    rng->lastGenerated = seed;
}

int RNG_generate(RNG* rng, const int limit) {
    rng->lastGenerated *= !(rng->lastGenerated == 0x560A);
    unsigned short s0 = (unsigned char)rng->lastGenerated << 8;
    s0 ^= rng->lastGenerated;
    rng->lastGenerated = ((s0 & 0xFF) << 8) | ((s0 & 0xFF00) >> 8);
    s0 = ((unsigned char)s0 << 1) ^ rng->lastGenerated;
    short s1 = (s0 >> 1) ^ 0xFF80;
    if (!(s0 & 1)) rng->lastGenerated = s1 ^ 0x1FF4;
    else rng->lastGenerated = s1 ^ 0x8180;
    return (int)(rng->lastGenerated) % limit;
}

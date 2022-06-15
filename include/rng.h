#pragma once

#define RAND(x) (rng.Generate() % x)

typedef struct {
    unsigned short lastGenerated;
} RNG;

void RNG_initialize(RNG* rng, const unsigned short seed);
int RNG_generate(RNG* rng, const int limit);
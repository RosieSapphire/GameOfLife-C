#pragma once

#include <SFML/Graphics.h>
#include "int2.h"

typedef struct {
    uint8_t state_now;
    uint8_t state_next;
    int2_t position;
} cell_t;

void cell_draw_to_buffer(const cell_t c, sfVertexArray* va, const uint32_t cell_pixels, const int2_t window_res);
uint32_t cell_count_neighbors(const int2_t centerPos, const cell_t* cells, const uint32_t cellCountX);


#include "cell.h"

void cell_draw_to_buffer(const cell_t c, sfVertexArray* va, const uint32_t cell_pixels, const int2_t window_res) {
    const uint32_t x_pixels = c.position.x * cell_pixels;
    const uint32_t y_pixels = c.position.y * cell_pixels;

    uint32_t x_cur;
    uint32_t y_cur;

    for(y_cur = y_pixels; y_cur < y_pixels + (uint32_t)cell_pixels; y_cur++) {
        for(x_cur = x_pixels; x_cur < x_pixels + (uint32_t)cell_pixels; x_cur++) {
            sfVertex* const pixel_cur = sfVertexArray_getVertex(va, y_cur * window_res.x + x_cur);
            pixel_cur->color = c.state_now ? sfGreen : sfBlack;
            pixel_cur->position.x = (float)x_cur;
            pixel_cur->position.y = (float)y_cur;
        }
    }
}

uint32_t cell_count_neighbors(const int2_t center_pos, const cell_t* cells, const uint32_t cell_count_x) {
    uint32_t cell_count = 0;

    uint32_t y;
    uint32_t x;
    for(y = center_pos.y - 1; y < center_pos.y + 2; y++) {
        for(x = center_pos.x - 1; x < center_pos.x + 2; x++) {
            if(y < 0 || x < 0 || (x == center_pos.x && y == center_pos.y)) continue;
            cell_count += (uint32_t)(cells[y * cell_count_x + x].state_now);
        }
    }

    return cell_count;
}


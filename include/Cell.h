#pragma once

#include <SFML/Graphics.h>
#include "Int2.h"

#define WINDOW_WIDTH        1920
#define WINDOW_HEIGHT       1080
#define CELL_COUNT_X        320
#define CELL_COUNT_Y        180
#define CELL_SIZE_PIXELS_X  (WINDOW_WIDTH/CELL_COUNT_X)
#define CELL_SIZE_PIXELS_Y  (WINDOW_HEIGHT/CELL_COUNT_Y)

typedef struct {
    bool currentState;
    bool intendedState;
    Int2 position;
} Cell;

void Cell_drawToBuffer(const Cell cell, sfVertexArray* screenBuffer);
void Cell_drawToBufferDebug(const Cell cell, sfVertexArray* screenBuffer);
int Cell_countNeighbors(const Int2 centerPos, const Cell* cells);
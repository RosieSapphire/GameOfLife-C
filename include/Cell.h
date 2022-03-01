#pragma once

#include <SFML/Graphics.h>
#include "Int2.h"

/*#define windowDimensions.x        1920
#define windowDimensions.y       1080
#define cellSizePixels  15
#define cellSizePixels  15
#define cellCountX        (windowDimensions.x/cellSizePixels)
#define cellCountY        (windowDimensions.y/cellSizePixels)*/

typedef struct {
    bool currentState;
    bool intendedState;
    Int2 position;
} Cell;

void Cell_drawToBuffer(const Cell cell, sfVertexArray* screenBuffer, const int cellSizePixels, const Int2 windowDimensions);
int Cell_countNeighbors(const Int2 centerPos, const Cell* cells, const int cellCountX);
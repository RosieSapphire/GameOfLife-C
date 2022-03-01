#include "Cell.h"

void Cell_drawToBuffer(const Cell cell, sfVertexArray* screenBuffer, const int cellSizePixels, const Int2 windowDimensions) {
    const int xInPixels = cell.position.x * cellSizePixels;
    const int yInPixels = cell.position.y * cellSizePixels;

    int currentX;
    int currentY;

    for(currentY = yInPixels; currentY < yInPixels + (int)cellSizePixels; currentY++) {
        for(currentX = xInPixels; currentX < xInPixels + (int)cellSizePixels; currentX++) {
            sfVertex* const currentVert = sfVertexArray_getVertex(screenBuffer, currentY * windowDimensions.x + currentX);
            currentVert->color = cell.currentState ? sfGreen : sfBlack;
            currentVert->position = (sfVector2f){(float)currentX, (float)currentY};
        }
    }
}

int Cell_countNeighbors(const Int2 centerPos, const Cell* cells, const int cellCountX) {
    int cellCount = 0;

    int y;
    int x;
    for(y = centerPos.y - 1; y < centerPos.y + 2; y++) {
        for(x = centerPos.x - 1; x < centerPos.x + 2; x++) {
            if(y < 0 || x < 0 || (x == centerPos.x && y == centerPos.y)) continue;
            cellCount += (int)(cells[y * cellCountX + x].currentState);
        }
    }

    return cellCount;
}
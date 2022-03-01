#include "Cell.h"

void Cell_drawToBuffer(const Cell cell, sfVertexArray* screenBuffer) {
    const int xInPixels = cell.position.x * CELL_SIZE_PIXELS_X;
    const int yInPixels = cell.position.y * CELL_SIZE_PIXELS_Y;

    int currentX;
    int currentY;

    for(currentY = yInPixels; currentY < yInPixels + (int)CELL_SIZE_PIXELS_Y; currentY++) {
        for(currentX = xInPixels; currentX < xInPixels + (int)CELL_SIZE_PIXELS_X; currentX++) {
            sfVertex* const currentVert = sfVertexArray_getVertex(screenBuffer, currentY * WINDOW_WIDTH + currentX);
            currentVert->color = cell.currentState ? sfGreen : sfBlack;
            currentVert->position = (sfVector2f){(float)currentX, (float)currentY};
        }
    }
}

void Cell_drawToBufferDebug(const Cell debugCell, sfVertexArray* screenBuffer) {
    const int xInPixels = debugCell.position.x * CELL_SIZE_PIXELS_X;
    const int yInPixels = debugCell.position.y * CELL_SIZE_PIXELS_Y;
    int currentX;
    int currentY;
    for(currentY = yInPixels; currentY < yInPixels + (int)CELL_SIZE_PIXELS_Y; currentY++) {
        for(currentX = xInPixels; currentX < xInPixels + (int)CELL_SIZE_PIXELS_X; currentX++) {
            sfVertex* const currentVert = sfVertexArray_getVertex(screenBuffer, currentY * WINDOW_WIDTH + currentX);
            currentVert->color = sfRed;
            currentVert->position = (sfVector2f){(float)currentX, (float)currentY};
        }
    }
}

int Cell_countNeighbors(const Int2 centerPos, const Cell* cells) {
    int cellCount = 0;

    int y;
    int x;
    for(y = centerPos.y - 1; y < centerPos.y + 2; y++) {
        for(x = centerPos.x - 1; x < centerPos.x + 2; x++) {
            if(y < 0 || x < 0 || (x == centerPos.x && y == centerPos.y)) continue;
            cellCount += (int)(cells[y * CELL_COUNT_X + x].currentState);
        }
    }

    return cellCount;
}
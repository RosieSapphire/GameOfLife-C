#include <stdbool.h>
#include <SFML/Graphics.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Cell.h"

#define WINDOW_SIZE         {windowDimensions.x, windowDimensions.y}
#define WINDOW_BIT_DEPTH    8
#define WINDOW_TITLE        "The Game of Life"

int main() {
    // prompt user for custom tickrate
    char customRateResponse;
    bool useCustomSettings;

    int gameUpdateRateMilli = 4000;
    int cellSizePixels = 4;

    printf("Use Custom Settings? (Enter/Return if no): ");
    scanf("%c", &customRateResponse);
    useCustomSettings = (customRateResponse == 'y');

    if(useCustomSettings) {
        printf("Enter Tickrate (Default = %d): ", gameUpdateRateMilli);
        scanf("%d", &gameUpdateRateMilli);
        
        printf("Enter Cell Size (Default = %d): ", cellSizePixels);
        scanf("%d", &cellSizePixels);
        cellSizePixels += (cellSizePixels < 2);
    }

    const float gameUpdateRateSecond = (float)(gameUpdateRateMilli) / 100000.0f;

    float timePassed = 0.0f;

    srand((unsigned int)time(NULL));

    const sfVector2i monitorSize = {sfVideoMode_getDesktopMode().width, sfVideoMode_getDesktopMode().height};
    const Int2 windowDimensions = {sfVideoMode_getDesktopMode().width, sfVideoMode_getDesktopMode().height};
    sfRenderWindow* renderWindow = sfRenderWindow_create((sfVideoMode){windowDimensions.x, windowDimensions.y, WINDOW_BIT_DEPTH}, WINDOW_TITLE, sfFullscreen, NULL);

    const int cellCountX = (windowDimensions.x/cellSizePixels);
    const int cellCountY = (windowDimensions.y/cellSizePixels);


    sfClock* clock = sfClock_create();

    sfVertexArray* screenBuffer = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(screenBuffer, sfPoints);
    sfVertexArray_resize(screenBuffer, windowDimensions.x * windowDimensions.y);

    // initializing cells
    Cell* cells = (Cell*)calloc(cellCountX * cellCountY, sizeof(Cell));

    Int2 currentCellPos;
    for(currentCellPos.y = 0; currentCellPos.y < cellCountY; currentCellPos.y++) {
        for(currentCellPos.x = 0; currentCellPos.x < cellCountX; currentCellPos.x++) {
            cells[currentCellPos.y * cellCountX + currentCellPos.x].position = (Int2){currentCellPos.x, currentCellPos.y};
            cells[currentCellPos.y * cellCountX + currentCellPos.x].intendedState = rand() % 2;
        }
    }

    // window loop
    bool windowClose;
    do {
        windowClose = !sfRenderWindow_isOpen(renderWindow) || sfKeyboard_isKeyPressed(sfKeyEscape);

        const float timeDelta = (float)(sfClock_restart(clock).microseconds) / 1000000.0f;
        timePassed += timeDelta;

        { // poll events
            sfEvent e;
            while(sfRenderWindow_pollEvent(renderWindow, &e)) {
                if(e.type == sfEvtClosed) {
                    sfRenderWindow_close(renderWindow);
                }
            }
        }

        const bool readyToTick = timePassed >= gameUpdateRateSecond;
        if(!readyToTick) continue;

        for(currentCellPos.y = 0; currentCellPos.y < cellCountY; currentCellPos.y++) {
            for(currentCellPos.x = 0; currentCellPos.x < cellCountX; currentCellPos.x++) {
                // update cell state before drawing
                cells[currentCellPos.y * cellCountX + currentCellPos.x].currentState = cells[currentCellPos.y * cellCountX + currentCellPos.x].intendedState;
                Cell_drawToBuffer(cells[currentCellPos.y * cellCountX + currentCellPos.x], screenBuffer, cellSizePixels, windowDimensions);
            }
        }

        // update cells intended state for next cycle
        for(currentCellPos.y = 0; currentCellPos.y < cellCountY; currentCellPos.y++) {
            for(currentCellPos.x = 0; currentCellPos.x < cellCountX; currentCellPos.x++) {
                Cell* currentCell = &cells[currentCellPos.y * cellCountX + currentCellPos.x];
                const int currentCellNeighbors = Cell_countNeighbors((Int2){currentCellPos.x, currentCellPos.y}, cells, cellCountX);
                const bool currentCellIsAlive = cells[currentCellPos.y * cellCountX + currentCellPos.x].currentState;

                currentCell->intendedState *= (currentCellNeighbors >= 2) && currentCellIsAlive;
                currentCell->intendedState *= (currentCellNeighbors <= 3) && currentCellIsAlive;
                if(!currentCellIsAlive) {
                    currentCell->intendedState = (currentCellNeighbors == 3);
                }
            }
        }

        timePassed = 0.0f;

        // draw everything out to the window
        sfRenderWindow_clear(renderWindow, sfBlack);
        sfRenderWindow_drawVertexArray(renderWindow, screenBuffer, NULL);
        sfRenderWindow_display(renderWindow);
    } while(!windowClose);

    sfVertexArray_destroy(screenBuffer);
    sfClock_destroy(clock);
    sfRenderWindow_destroy(renderWindow);

    return 0;
}
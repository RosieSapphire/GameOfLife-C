#include <stdbool.h>
#include <SFML/Graphics.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Cell.h"

#define WINDOW_SIZE         {WINDOW_WIDTH, WINDOW_HEIGHT}
#define WINDOW_BIT_DEPTH    8
#define WINDOW_TITLE        "The Game of Life"

#define CENTER_WINDOW_ON_SCREEN(X) sfRenderWindow_setPosition(X, (sfVector2i){(monitorSize.x * 0.5f) - ((float)WINDOW_WIDTH * 0.5f), (monitorSize.y * 0.5f) - ((float)WINDOW_HEIGHT * 0.5f)});

int main() {
    // prompt user for custom tickrate
    char customRateResponse;
    bool useCustomRate;
    int gameUpdateRateMilli = 8000;
    printf("Use Custom Tickrate? (Default = 8000) (Return if no): ");
    scanf("%c", &customRateResponse);
    useCustomRate = (customRateResponse == 0 || customRateResponse == 'y');

    if(useCustomRate) {
        printf("Enter Tickrate: ");
        scanf("%d", &gameUpdateRateMilli);
    }

    const float gameUpdateRateSecond = (float)(gameUpdateRateMilli) / 100000.0f;

    float timePassed = 0.0f;

    srand((unsigned int)time(NULL));

    sfRenderWindow* renderWindow = sfRenderWindow_create((sfVideoMode){WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BIT_DEPTH}, WINDOW_TITLE, sfClose, NULL);
    const sfVector2i monitorSize = {sfVideoMode_getDesktopMode().width, sfVideoMode_getDesktopMode().height};
    CENTER_WINDOW_ON_SCREEN(renderWindow);

    sfClock* clock = sfClock_create();

    sfVertexArray* screenBuffer = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(screenBuffer, sfPoints);
    sfVertexArray_resize(screenBuffer, WINDOW_WIDTH * WINDOW_HEIGHT);

    // initializing cells
    Cell cells[CELL_COUNT_X * CELL_COUNT_Y] = { false, false };

    int xInCells;
    int yInCells;
    for(yInCells = 0; yInCells < CELL_COUNT_Y; yInCells++) {
        for(xInCells = 0; xInCells < CELL_COUNT_X; xInCells++) {
            cells[yInCells * CELL_COUNT_X + xInCells].position = (Int2){xInCells, yInCells};
            cells[yInCells * CELL_COUNT_X + xInCells].intendedState = rand() % 2;
        }
    }

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
        if(readyToTick) {
            for(yInCells = 0; yInCells < CELL_COUNT_Y; yInCells++) {
                for(xInCells = 0; xInCells < CELL_COUNT_X; xInCells++) {
                    // update cell state before drawing
                    cells[yInCells * CELL_COUNT_X + xInCells].currentState = cells[yInCells * CELL_COUNT_X + xInCells].intendedState;
                    Cell_drawToBuffer(cells[yInCells * CELL_COUNT_X + xInCells], screenBuffer);
                }
            }

            // update cells intended state for next cycle
            for(yInCells = 0; yInCells < CELL_COUNT_Y; yInCells++) {
                for(xInCells = 0; xInCells < CELL_COUNT_X; xInCells++) {
                    Cell* currentCell = &cells[yInCells * CELL_COUNT_X + xInCells];
                    const int currentCellNeighbors = Cell_countNeighbors((Int2){xInCells, yInCells}, cells);
                    const bool currentCellIsAlive = cells[yInCells * CELL_COUNT_X + xInCells].currentState;
                    if(currentCellIsAlive) {
                        if(currentCellNeighbors < 2) {
                            currentCell->intendedState = false;
                        } else if(currentCellNeighbors > 3) {
                            currentCell->intendedState = false;
                        }
                    } else {
                        if(currentCellNeighbors == 3) {
                            currentCell->intendedState = true;
                        }
                    }
                }
            }

            timePassed = 0.0f;
        }

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
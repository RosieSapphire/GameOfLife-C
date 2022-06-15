#include <stdbool.h>
#include <SFML/Graphics.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cell.h"
#include "int2.h"

#define WINDOW_SIZE         {desktop_mode.width, desktop_mode.height}
#define WINDOW_BIT_DEPTH    8
#define WINDOW_TITLE        "The Game of Life"

int main() {
    bool window_close;
	bool ready_to_tick;
	char *c;

    sfEvent e;
	sfVideoMode desktop_mode;
	sfRenderWindow* render_window;
	sfVertexArray *screen_buffer;
	sfClock *clock;
	int2_t monitor_size;

    /* prompt user for custom tickrate */
    char custom_rate_responce;
    bool use_custom_settings;

    int game_update_rate_milli = 4000;
    int cell_size_pixels = 4;
    const float game_update_rate_second = (float)(game_update_rate_milli) / 100000.0f;

    float time_elapsed = 0.0f;
	float time_delta;

	int cell_count_x;
	int cell_count_y;
    int2_t cur_cell_pos;

	cell_t* cells;

	c = malloc(sizeof(char));
    printf("Use Custom Settings? (Enter/Return if no): ");
    *c = scanf("%c", &custom_rate_responce);
    use_custom_settings = (custom_rate_responce == 'y');

    if(use_custom_settings) {
        printf("Enter Tickrate (Default = %d): ", game_update_rate_milli);
        *c = scanf("%d", &game_update_rate_milli);
        
        printf("Enter cell_t Size (Default = %d): ", cell_size_pixels);
        *c = scanf("%d", &cell_size_pixels);
        cell_size_pixels += (cell_size_pixels < 2);
    }

    srand((unsigned int)time(NULL));

	desktop_mode = sfVideoMode_getDesktopMode();
    monitor_size = int2_create(desktop_mode.width, desktop_mode.height);
    render_window = sfRenderWindow_create(desktop_mode, WINDOW_TITLE, sfFullscreen, NULL);

    cell_count_x = (desktop_mode.width / cell_size_pixels);
    cell_count_y = (desktop_mode.height / cell_size_pixels);

    clock = sfClock_create();

    screen_buffer = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(screen_buffer, sfPoints);
    sfVertexArray_resize(screen_buffer, desktop_mode.width * desktop_mode.height);

    /* initializing cells */
    cells = (cell_t*)calloc(cell_count_x * cell_count_y, sizeof(cell_t));

    for(cur_cell_pos.y = 0; cur_cell_pos.y < cell_count_y; cur_cell_pos.y++) {
        for(cur_cell_pos.x = 0; cur_cell_pos.x < cell_count_x; cur_cell_pos.x++) {
            cells[cur_cell_pos.y * cell_count_x + cur_cell_pos.x].position = int2_create(cur_cell_pos.x, cur_cell_pos.y);
            cells[cur_cell_pos.y * cell_count_x + cur_cell_pos.x].state_next = rand() % 2;
        }
    }

    /* window loop */
    do {
        window_close = !sfRenderWindow_isOpen(render_window) || sfKeyboard_isKeyPressed(sfKeyEscape);

        time_delta = sfTime_asSeconds(sfClock_restart(clock));
        time_elapsed += time_delta;

        /* poll events */
        while(sfRenderWindow_pollEvent(render_window, &e)) {
            if(e.type == sfEvtClosed) {
                sfRenderWindow_close(render_window);
            }
        }

        ready_to_tick = time_elapsed >= game_update_rate_second;
        if(!ready_to_tick) continue;

        for(cur_cell_pos.y = 0; cur_cell_pos.y < cell_count_y; cur_cell_pos.y++) {
            for(cur_cell_pos.x = 0; cur_cell_pos.x < cell_count_x; cur_cell_pos.x++) {
                /* update cell state before drawing */
                cells[cur_cell_pos.y * cell_count_x + cur_cell_pos.x].state_now = cells[cur_cell_pos.y * cell_count_x + cur_cell_pos.x].state_next;
                cell_draw_to_buffer(cells[cur_cell_pos.y * cell_count_x + cur_cell_pos.x], screen_buffer, cell_size_pixels, monitor_size);
            }
        }

        /* update cells intended state for next cycle */
        for(cur_cell_pos.y = 0; cur_cell_pos.y < cell_count_y; cur_cell_pos.y++) {
            for(cur_cell_pos.x = 0; cur_cell_pos.x < cell_count_x; cur_cell_pos.x++) {
                cell_t* cell_cur = &cells[cur_cell_pos.y * cell_count_x + cur_cell_pos.x];
                const int cell_cur_neighbors = cell_count_neighbors(int2_create(cur_cell_pos.x, cur_cell_pos.y), cells, cell_count_x);
                const bool cell_cur_alive = cells[cur_cell_pos.y * cell_count_x + cur_cell_pos.x].state_now;

                cell_cur->state_next *= (cell_cur_neighbors >= 2) && cell_cur_alive;
                cell_cur->state_next *= (cell_cur_neighbors <= 3) && cell_cur_alive;
                if(!cell_cur_alive) {
                    cell_cur->state_next = (cell_cur_neighbors == 3);
                }
            }
        }

        time_elapsed = 0.0f;

        /* draw everything out to the window */
        sfRenderWindow_clear(render_window, sfBlack);
        sfRenderWindow_drawVertexArray(render_window, screen_buffer, NULL);
        sfRenderWindow_display(render_window);
    } while(!window_close);

    sfVertexArray_destroy(screen_buffer);
    sfClock_destroy(clock);
    sfRenderWindow_destroy(render_window);

	free(c);

    return 0;
}

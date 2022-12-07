/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "datastructure.h"

window_t *Window(char *gameName, sfVector2i size, int bits)
{
    window_t *window = malloc(sizeof(window_t));

    if (window == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }
    
    // Set variables
    window->name = strdup(gameName);
    window->mode.width = size.x;
    window->mode.height = size.y;
    window->mode.bitsPerPixel = bits;
    window->currSize = (sfVector2i){size.x, size.y};
    window->window = sfRenderWindow_create(
        window->mode,
        window->name,
        sfClose,
        NULL
    );
    if (!window->window) {
        write(2, "Can't load window.\n", 19);
        return NULL;
    }
    sfRenderWindow_setVerticalSyncEnabled(window->window, 1);
    return window;
}

void Dtr_Window(window_t *window)
{
    free(window->name);
    sfRenderWindow_destroy(window->window);
    free(window);
}
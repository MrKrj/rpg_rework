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
#include "prototypes.h"

char *hairsFiles[] = {
    "assets/player/bowl_idle.png",
    "assets/player/curly_idle.png",
    "assets/player/long_idle.png",
    "assets/player/mophair_idle.png",
    "assets/player/short_idle.png",
    "assets/player/spike_idle.png",
};
int idx = 1;

/* BUTTON CALLS */

void Game_changeLeft(UNUSED core_t *core)
{
    gameObject_t *tmp = core->curr->entities;
    graphics_t *graphic;

    while (tmp != NULL) {
        if (strcmp(tmp->name, "hair") == 0) {
            idx++;
            if (idx == 6)
                idx = 0;
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            Graphics_updateSprite(core, graphic, hairsFiles[idx]);
        }
        tmp = tmp->next;
    }
}

void Game_changeRight(UNUSED core_t *core)
{
    gameObject_t *tmp = core->curr->entities;
    graphics_t *graphic;

    while (tmp != NULL) {
        if (strcmp(tmp->name, "hair") == 0) {
            idx--;
            if (idx == -1)
                idx = 5;
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            Graphics_updateSprite(core, graphic, hairsFiles[idx]);
        }
        tmp = tmp->next;
    }
}
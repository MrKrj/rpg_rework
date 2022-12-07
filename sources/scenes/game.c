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
int idx = 0;

/* BUTTON CALLS */

void Game_changeLeft(UNUSED core_t *core, int on)
{
    gameObject_t *tmp = core->curr->entities;
    graphics_t *graphic;
    sfIntRect rect;

    while (tmp != NULL) {
        if (on == TRUE && strcmp(tmp->name, "hair") == 0) {
            idx++;
            if (idx == 6)
                idx = 0;
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            Graphics_updateSprite(core, graphic, hairsFiles[idx]);
        }
        if (strcmp(tmp->name, "change_left") == 0) {
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            rect = sfSprite_getTextureRect(graphic->sprite);
            if (on == FALSE)
                rect.left = 2 * graphic->size.x;
            else
                rect.left = graphic->size.x;
            sfSprite_setTextureRect(graphic->sprite, rect);
        }
        tmp = tmp->next;
    }
}

void Game_changeRight(UNUSED core_t *core, int on)
{
    gameObject_t *tmp = core->curr->entities;
    graphics_t *graphic;
    sfIntRect rect;

    while (tmp != NULL) {
        if (on == TRUE && strcmp(tmp->name, "hair") == 0) {
            idx--;
            if (idx == -1)
                idx = 5;
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            Graphics_updateSprite(core, graphic, hairsFiles[idx]);
        }
        if (strcmp(tmp->name, "change_right") == 0) {
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            rect = sfSprite_getTextureRect(graphic->sprite);
            if (on == FALSE)
                rect.left = 2 * graphic->size.x;
            else
                rect.left = graphic->size.x;
            sfSprite_setTextureRect(graphic->sprite, rect);
        }
        tmp = tmp->next;
    }
}

/* HOVER CALLS */

void Game_hover_ChangeRight(core_t *core, int on)
{
    gameObject_t *tmp = core->curr->entities;
    graphics_t *graphic;

    while (tmp != NULL) {
        if (strcmp(tmp->name, "change_right") == 0) {
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            sfIntRect rect = sfSprite_getTextureRect(graphic->sprite);
            if (on == TRUE)
                rect.left = graphic->size.x;
            else
                rect.left = 0;
            sfSprite_setTextureRect(graphic->sprite, rect);
        }
        tmp = tmp->next;
    }
}

void Game_hover_ChangeLeft(core_t *core, int on)
{
    gameObject_t *tmp = core->curr->entities;
    graphics_t *graphic;

    while (tmp != NULL) {
        if (strcmp(tmp->name, "change_left") == 0) {
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            sfIntRect rect = sfSprite_getTextureRect(graphic->sprite);
            if (on == TRUE)
                rect.left = graphic->size.x;
            else
                rect.left = 0;
            sfSprite_setTextureRect(graphic->sprite, rect);
        }
        tmp = tmp->next;
    }
}
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

/* ANY_EVENT CALLS */

void Intro_pass(UNUSED core_t* core, UNUSED int param)
{
    gameObject_t *tmp = core->curr->entities;
    comp_t *comp;
    graphics_t *graphic;
    sfVector2f pos;

    while (tmp != NULL) {
        comp = tmp->comps->comps;
        while (comp != NULL) {
            if (strcmp(tmp->name, "fadeIn") == 0 && comp->type == GRAPHICS) {
                graphic = toGraphics(comp);
                pos = sfSprite_getPosition(graphic->sprite);
                if (graphic->name != NULL && strcmp(graphic->name, "loading_bar") == 0 && pos.y == 2000) {
                    pos.y = -2000 - (pos.x / 40 * 100);
                    sfSprite_setPosition(graphic->sprite, pos);
                    sfMusic_play(toMusic(tmp->comps->getComp(tmp->comps, MUSIC, 0))->music);
                }
            }
            comp = comp->next;
        }
        tmp = tmp->next;
    }
}

/* CUSTOM UPDATE */

int Intro_update(UNUSED core_t *core)
{
    gameObject_t *tmp = core->curr->entities;
    comp_t *comp;
    graphics_t *graphic;
    sfVector2f pos;

    while (tmp != NULL) {
        comp = tmp->comps->comps;
        while (comp != NULL) {
            if (strcmp(tmp->name, "fadeIn") == 0 && comp->type == GRAPHICS) {
                graphic = toGraphics(comp);
                if (graphic->name != NULL && strcmp(graphic->name, "loading_bar") == 0) {
                    pos = sfSprite_getPosition(graphic->sprite);
                    if (pos.y < -100) {
                        pos.y += ((float)2000 * core->time->elapsed);
                        sfSprite_setPosition(graphic->sprite, pos);
                    } else if (pos.x == 1240 && pos.y >= -100 && pos.y <= 100) {
                        core->tmp = core->curr;
                        core->curr = Scene(core, "contents/game/game.scene", GAME, &Game_update, TRUE);
                        sfMusic_stop(toMusic(tmp->comps->getComp(tmp->comps, MUSIC, 0))->music);
                        return 0;
                    }
                }
            }
            comp = comp->next;
        }
        tmp = tmp->next;
    }
    return 0;
}
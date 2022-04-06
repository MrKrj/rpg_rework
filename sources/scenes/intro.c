/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include "datastructure.h"
#include "prototypes.h"


static int event(UNUSED core_t *core)
{
    return 0;
}

static int update(UNUSED core_t *core)
{
    gameObject_t *tmp = core->curr->entities;
    comp_t *comp;
    graphics_t *graphic;
    sfIntRect rect;

    core->curr->elapsed += core->time->elapsed;
    while (tmp != NULL) {
        comp = tmp->comps->getComp(tmp->comps, GRAPHICS);
        if (comp == NULL) {
            tmp = tmp->next;
            continue;
        }
        graphic = toGraphics(comp);
        if (graphic->animated == FALSE)
            continue;
        graphic->elapsed += core->time->elapsed;
        rect = sfSprite_getTextureRect(graphic->sprite);
        if (graphic->elapsed > graphic->passed) {
            rect.left += graphic->size.x;
            if (rect.left == graphic->size.x * graphic->grid.x) {
                rect.left = 0;
                rect.top += graphic->size.y;
                if (rect.top == graphic->size.y * graphic->grid.y)
                    rect.top = 0;
            }
            sfSprite_setTextureRect(graphic->sprite, rect);
            graphic->elapsed -= graphic->passed;
        }
        tmp = tmp->next;
    }
    return 0;
}

static int display(UNUSED core_t *core)
{
    gameObject_t *tmp = core->curr->entities;
    comp_t *comp;

    while (tmp != NULL) {
        comp = tmp->comps->getComp(tmp->comps, GRAPHICS);
        if (comp != NULL) {
            sfRenderWindow_drawSprite(
                core->window->window,
                toGraphics(comp)->sprite,
                NULL
            );
        }
        comp = tmp->comps->getComp(tmp->comps, TEXT);
        if (comp != NULL) {
            sfRenderWindow_drawText(
                core->window->window,
                toText(comp)->text,
                NULL
            );
        }
        tmp = tmp->next;
    }
    return 0;
}

scene_t *Intro(core_t *core)
{
    scene_t *intro = malloc(sizeof(scene_t));

    if (intro == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }

    // Set methods
    intro->type = INTRO;
    intro->entities = GameObjectsFromConfig(core, "contents/scenes/intro.ini");
    intro->canBeDestroyed = TRUE;
    intro->elapsed = 0.f;
    intro->event = &event;
    intro->update = &update;
    intro->display = &display;

    return intro;
}

void Dtr_Intro(scene_t *intro)
{
    free(intro);
}
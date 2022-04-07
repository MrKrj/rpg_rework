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
        if (graphic->animated == FALSE) {
            tmp = tmp->next;
            continue;
        }
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

scene_t *Menu(core_t *core)
{
    scene_t *menu = malloc(sizeof(scene_t));

    if (menu == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }

    // Set methods
    menu->type = MENU;
    menu->entities = GameObjectsFromConfig(core, "contents/scenes/menu.ini");
    menu->canBeDestroyed = TRUE;
    menu->elapsed = 0.f;
    menu->event = &event;
    menu->update = &update;
    menu->display = &display;

    return menu;
}

void Dtr_Menu(scene_t *menu)
{
    free(menu);
}
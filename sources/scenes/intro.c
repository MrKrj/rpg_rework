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

/* BUTTON CALLS */

void Intro_passToMenu(UNUSED core_t *core) {
    Dtr_Intro(core->curr);
    core->curr = Menu(core);
}

/* CLASS */

static int event(UNUSED core_t *core)
{
    gameObject_t *tmp = core->curr->entities;
    comp_t *comp;
    button_t *button;
    graphics_t *graphic;
    sfVector2f mousePos;
    sfVector2f spritePos;
    sfVector2f spriteScale;

    if (core->window->event.type == sfEvtMouseButtonPressed || core->window->event.type == sfEvtMouseButtonReleased) {
        mousePos = (sfVector2f){(float)core->window->event.mouseButton.x, (float)core->window->event.mouseButton.y};
        while (tmp != NULL) {
            comp = tmp->comps->getComp(tmp->comps, BUTTON);
            if (comp == NULL) {
                tmp = tmp->next;
                continue;
            }
            button = toButton(comp);
            graphic = toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS));
            spritePos = sfSprite_getPosition(graphic->sprite);
            spriteScale = sfSprite_getScale(graphic->sprite);
            if ((mousePos.x >= spritePos.x && mousePos.y >= spritePos.y) &&
                (mousePos.x <= spritePos.x + (graphic->size.x * (int)spriteScale.x) &&
                mousePos.y <= spritePos.y + (graphic->size.y) * (int)spriteScale.y)) {
                button->onClicked(core);
                return 0;
            }
            tmp = tmp->next;
        }
    }
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
    Dtr_AllGameObjects(intro->entities);
    free(intro);
}
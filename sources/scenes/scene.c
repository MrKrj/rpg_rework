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

/* CLASS */

static int button_is_cliked(gameObject_t *gO, sfVector2f mousePos)
{
    graphics_t *graphic = toGraphics(gO->comps->getComp(gO->comps, GRAPHICS));
    sfVector2f spritePos = sfSprite_getPosition(graphic->sprite);
    sfVector2f spriteScale = sfSprite_getScale(graphic->sprite);
    if ((mousePos.x >= spritePos.x && mousePos.y >= spritePos.y) &&
        (mousePos.x <= spritePos.x + (graphic->size.x * (int)spriteScale.x) &&
        mousePos.y <= spritePos.y + (graphic->size.y) * (int)spriteScale.y)) {
        return TRUE;
    }
    return FALSE;
}

static int clicked(core_t *core)
{
    gameObject_t *tmp = core->curr->entities;
    comp_t *comp;
    button_t *button;
    sfVector2f mousePos = (sfVector2f) {
        (float)core->window->event.mouseButton.x,
        (float)core->window->event.mouseButton.y
    };

    while (tmp != NULL) {
        comp = tmp->comps->getComp(tmp->comps, BUTTON);
        if (comp == NULL) {
            tmp = tmp->next;
            continue;
        }
        button = toButton(comp);
        if (button_is_cliked(tmp, mousePos) == TRUE) {
            button->onClicked(core);
            return TRUE;
        }
        tmp = tmp->next;
    }
    return FALSE;
}

static int event(UNUSED core_t *core)
{
    if (core->window->event.type == sfEvtMouseButtonReleased) {
        if (clicked(core) == TRUE)
            return TRUE;
    }
    return TRUE;
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

scene_t *Scene(core_t *core, char *path, scene_type_t type, int canBeDestroyed)
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (scene == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }

    // Set methods
    scene->type = type;
    scene->entities = GameObjectsFromConfig(core, path);
    scene->canBeDestroyed = canBeDestroyed;
    scene->elapsed = 0.f;
    scene->event = &event;
    scene->update = &update;
    scene->display = &display;

    return scene;
}

void Dtr_Scene(scene_t *scene)
{
    Dtr_AllGameObjects(scene->entities);
    free(scene);
}
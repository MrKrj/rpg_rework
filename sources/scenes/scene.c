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

static int isIn(core_t *core, gameObject_t *gO, sfVector2f mousePos)
{
    graphics_t *graphic = toGraphics(gO->comps->getComp(gO->comps, GRAPHICS, 0));
    sfVector2f spritePos = sfSprite_getPosition(graphic->sprite);
    sfVector2f spriteScale = sfSprite_getScale(graphic->sprite);
    float fx = core->window->currSize.x / core->window->mode.width;
    float fy = core->window->currSize.y / core->window->mode.height;

    if ((mousePos.x >= spritePos.x * fx && mousePos.y >= spritePos.y * fy) &&
        (mousePos.x <= (spritePos.x + (graphic->size.x * (int)spriteScale.x)) * fx &&
        mousePos.y <= (spritePos.y + (graphic->size.y * (int)spriteScale.y)) * fy)) {
        return TRUE;
    }
    return FALSE;
}

static int clicked(core_t *core, int on)
{
    gameObject_t *gO = core->curr->entities;
    comp_t *comp;
    button_t *button;
    sfVector2f mousePos = (sfVector2f) {
        (float)core->window->event.mouseButton.x,
        (float)core->window->event.mouseButton.y
    };

    while (gO != NULL) {
        comp = gO->comps->comps;
        while (comp != NULL) {
            if (comp->type == BUTTON) {
                button = toButton(comp);
                if (isIn(core, gO, mousePos) == TRUE) {
                    button->onClicked(core, on);
                    return TRUE;
                }
            }
            comp = comp->next;
        }
        gO = gO->next;
    }
    return FALSE;
}

static void hover(core_t *core)
{
    gameObject_t *gO = core->curr->entities;
    comp_t *comp;
    hover_t *hover;
    sfVector2f mousePos = (sfVector2f) {
        (float)core->window->event.mouseMove.x,
        (float)core->window->event.mouseMove.y
    };

    while (gO != NULL) {
        comp = gO->comps->comps;
        while (comp != NULL) {
            if (comp->type == HOVER) {
                hover = toHover(comp);
                if (isIn(core, gO, mousePos) == TRUE)
                    hover->onHover(core, TRUE);
                else
                    hover->onHover(core, FALSE);
            }
            comp = comp->next;
        }
        gO = gO->next;
    }
}

static void keyPressed(core_t *core)
{
    gameObject_t *gO = core->curr->entities;
    comp_t *comp;
    anyEvent_t *anyEvent;

    while (gO != NULL) {
        comp = gO->comps->getComp(gO->comps, ANY_EVENT, 0);
        if (comp == NULL) {
            gO = gO->next;
            continue;
        }
        anyEvent = toAnyEvent(comp);
        anyEvent->onKeyPressed(core, DEFAULT);
        gO = gO->next;
    }
}

static void mousePressed(core_t *core)
{
    gameObject_t *gO = core->curr->entities;
    comp_t *comp;
    anyEvent_t *anyEvent;

    while (gO != NULL) {
        comp = gO->comps->getComp(gO->comps, ANY_EVENT, 0);
        if (comp == NULL) {
            gO = gO->next;
            continue;
        }
        anyEvent = toAnyEvent(comp);
        anyEvent->onMousePressed(core, DEFAULT);
        gO = gO->next;
    }
}

static int event(UNUSED core_t *core)
{
    if (core->window->event.type == sfEvtKeyPressed) {
        keyPressed(core);
    }
    if (core->window->event.type == sfEvtMouseButtonReleased) {
        if (clicked(core, TRUE) == TRUE)
            return TRUE;
    }
    if (core->window->event.type == sfEvtMouseButtonPressed) {
        mousePressed(core);
        if (clicked(core, FALSE) == TRUE)
            return TRUE;
    }
    if (core->window->event.type == sfEvtMouseMoved) {
        hover(core);
    }
    if (core->window->event.type == sfEvtResized) {
        core->window->currSize.x = core->window->event.size.width;
        core->window->currSize.y = core->window->event.size.height;
    }
    return TRUE;
}

static void animate(core_t *core, graphics_t *graphic)
{
    sfIntRect rect = sfSprite_getTextureRect(graphic->sprite);

    graphic->elapsed += core->time->elapsed;
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
}

static void parallax(core_t *core, graphics_t *graphic)
{
    sfVector2f pos = sfSprite_getPosition(graphic->sprite);

    pos.x += ((float)graphic->velocity * core->time->elapsed);
    if ((graphic->velocity > 0 && pos.x > core->window->mode.width) || (graphic->velocity < 0 && pos.x < 0))
        pos.x = graphic->pos.x;
    sfSprite_setPosition(graphic->sprite, pos);
}

static int update(UNUSED core_t *core)
{
    gameObject_t *tmp = core->curr->entities;
    comp_t *comp;
    graphics_t *graphic;

    core->curr->elapsed += core->time->elapsed;
    while (tmp != NULL) {
        comp = tmp->comps->comps;
        while (comp != NULL) {
            if (comp->type == GRAPHICS) {
                graphic = toGraphics(comp);
                if (graphic->animated == TRUE)
                    animate(core, graphic);
                if (graphic->parallax == TRUE)
                    parallax(core, graphic);
            }
            comp = comp->next;
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
        comp = tmp->comps->comps;
        while (comp != NULL) {
            if (comp->type == GRAPHICS)
                sfRenderWindow_drawSprite(
                    core->window->window,
                    toGraphics(comp)->sprite,
                    NULL
                );
            if (comp->type == TEXT)
                sfRenderWindow_drawText(
                    core->window->window,
                    toText(comp)->text,
                    NULL
                );
            comp = comp->next;
        }
        tmp = tmp->next;
    }
    return 0;
}

scene_t *Scene(core_t *core, char *path, scene_type_t type, int (*customUpdate)(core_t *core), int canBeDestroyed)
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
    scene->customUpdate = customUpdate;
    scene->display = &display;
    return scene;
}

void Dtr_Scene(scene_t *scene)
{
    Dtr_AllGameObjects(scene->entities);
    free(scene);
}
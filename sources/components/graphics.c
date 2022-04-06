/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "datastructure.h"
#include "prototypes.h"

graphics_t *toGraphics(comp_t *comp)
{
    if (comp->type != GRAPHICS)
        return NULL;
    return (graphics_t *)comp->comp;
}

static void setPath(core_t *core, graphics_t *component, tuple_t *tuple)
{
    component->sprite = core->sprites->getSpriteByName(core->sprites, tuple->value);
    if (component->sprite == NULL)
        component->sprite = core->sprites->addSprite(core->sprites, tuple->value, tuple->value);
}

static void setPosX(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    sfVector2f pos = sfSprite_getPosition(component->sprite);
    pos.x = atof(tuple->value);
    sfSprite_setPosition(component->sprite, pos);
}

static void setPosY(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    sfVector2f pos = sfSprite_getPosition(component->sprite);
    pos.y = atof(tuple->value);
    sfSprite_setPosition(component->sprite, pos);
}

static void setSizeX(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    sfVector2f size = sfSprite_getScale(component->sprite);
    size.x = atof(tuple->value);
    sfSprite_setScale(component->sprite, size);
}

static void setSizeY(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    sfVector2f size = sfSprite_getScale(component->sprite);
    size.y = atof(tuple->value);
    sfSprite_setScale(component->sprite, size);
}

static void setCol(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    component->grid.x = atoi(tuple->value);
}

static void setRow(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    component->grid.y = atoi(tuple->value);
}

static void setWidth(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    sfIntRect rect;
    if (component->sprite == NULL)
        return;
    rect = sfSprite_getTextureRect(component->sprite);
    rect.width = atoi(tuple->value);
    sfSprite_setTextureRect(component->sprite, rect);
    component->size.x = atoi(tuple->value);
}

static void setHeight(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    sfIntRect rect;
    if (component->sprite == NULL)
        return;
    rect = sfSprite_getTextureRect(component->sprite);
    rect.height = atoi(tuple->value);
    sfSprite_setTextureRect(component->sprite, rect);
    component->size.y = atoi(tuple->value);
}

static void setAnimed(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    component->animated = strcmp(tuple->value, "true") == 0 ? TRUE : FALSE;
}

static void setPassed(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    component->passed = atof(tuple->value);
}

typedef struct {
    char *key;
    void (*setParam)(core_t *, graphics_t *, tuple_t *);
} graphicsParamsCtor_t;

const graphicsParamsCtor_t graphicsParamsCtors[] = {
    {"path", &setPath},
    {"posX", &setPosX},
    {"posY", &setPosY},
    {"sizeX", &setSizeX},
    {"sizeY", &setSizeY},
    {"col", &setCol},
    {"row", &setRow},
    {"width", &setWidth},
    {"height", &setHeight},
    {"animated", &setAnimed},
    {"passed", &setPassed}
};

comp_t *Graphics(core_t *core, FILE *fp)
{
    tuple_t *tuple = NULL;
    comp_t *comp = malloc(sizeof(comp_t));
    graphics_t *component = malloc(sizeof(graphics_t));

    if (comp == NULL || component == NULL)
        return NULL;
    component->sprite = NULL;
    component->animated = FALSE;
    component->elapsed = 0.f;
    component->passed = 0.f;
    component->size = (sfVector2i){0, 0};
    component->grid = (sfVector2i){0, 0};
    do {
        tuple = TupleFromFile(fp);
        if (tuple != NULL) {
            for (int i = 0; i < 11; ++i)
                if (strcmp(tuple->key, graphicsParamsCtors[i].key) == 0)
                    graphicsParamsCtors[i].setParam(core, component, tuple);
            Dtr_Tuple(tuple);
        }
    } while (tuple != NULL);
    comp->type = GRAPHICS;
    comp->comp = component;
    comp->next = NULL;
    return comp;
}
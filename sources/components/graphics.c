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

void setPath(core_t *core, graphics_t *component, tuple_t *tuple)
{
    component->sprite = core->sprites->getSpriteByName(core->sprites, tuple->value);
    if (component->sprite == NULL)
        component->sprite = core->sprites->addSprite(core->sprites, tuple->value, tuple->value);
}

void setPosX(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    sfVector2f pos = sfSprite_getPosition(component->sprite);
    pos.x = atof(tuple->value);
    sfSprite_setPosition(component->sprite, pos);
}

void setPosY(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    sfVector2f pos = sfSprite_getPosition(component->sprite);
    pos.y = atof(tuple->value);
    sfSprite_setPosition(component->sprite, pos);
}

void setSizeX(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    sfVector2f size = sfSprite_getScale(component->sprite);
    size.x = atof(tuple->value);
    sfSprite_setScale(component->sprite, size);
}

void setSizeY(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    sfVector2f size = sfSprite_getScale(component->sprite);
    size.y = atof(tuple->value);
    sfSprite_setScale(component->sprite, size);
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
    {"sizeY", &setSizeY}
};

comp_t *Graphics(core_t *core, FILE *fp)
{
    tuple_t *tuple = NULL;
    comp_t *comp = malloc(sizeof(comp_t));
    graphics_t *component = malloc(sizeof(graphics_t));

    if (comp == NULL || component == NULL)
        return NULL;
    component->sprite = NULL;
    do {
        tuple = TupleFromFile(fp);
        if (tuple != NULL) {
            for (int i = 0; i < 5; ++i)
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
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

static void setName(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    component->name = strdup(tuple->value);
}

static void setPath(core_t *core, graphics_t *component, tuple_t *tuple)
{
    component->sprite = core->sprites->getSpriteByName(core->sprites, tuple->value);
    if (component->sprite == NULL)
        component->sprite = core->sprites->addSprite(core->sprites, tuple->value, tuple->value);
}

static void setPosX(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    sfVector2f pos;

    if (component->sprite == NULL)
        return;
    pos = sfSprite_getPosition(component->sprite);
    pos.x = atof(tuple->value);
    component->pos.x = pos.x;
    sfSprite_setPosition(component->sprite, pos);
}

static void setPosY(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    sfVector2f pos;

    if (component->sprite == NULL)
        return;
    pos = sfSprite_getPosition(component->sprite);
    pos.y = atof(tuple->value);
    component->pos.y = pos.y;
    sfSprite_setPosition(component->sprite, pos);
}

static void setSizeX(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    sfVector2f scale;

    if (component->sprite == NULL)
        return;
    scale = sfSprite_getScale(component->sprite);
    scale.x = atof(tuple->value);
    component->scale.x = scale.x;
    sfSprite_setScale(component->sprite, scale);
}

static void setSizeY(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    sfVector2f scale;

    if (component->sprite == NULL)
        return;
    scale = sfSprite_getScale(component->sprite);
    scale.y = atof(tuple->value);
    component->scale.y = scale.y;
    sfSprite_setScale(component->sprite, scale);
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

static void setParallax(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    component->parallax = strcmp(tuple->value, "true") == 0 ? TRUE : FALSE;
}

static void setVelocity(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    if (component->sprite == NULL)
        return;
    component->velocity = atoi(tuple->value);
}

static void setOpacity(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    sfColor color;

    if (component->sprite == NULL)
        return;
    color = sfSprite_getColor(component->sprite);
    color.a = atoi(tuple->value) * 100;
    component->opacity = color.a;
    sfSprite_setColor(component->sprite, color);
}

static void setDarkness(UNUSED core_t *core, graphics_t *component, tuple_t *tuple)
{
    sfColor color;

    if (component->sprite == NULL)
        return;
    color = sfSprite_getColor(component->sprite);
    color.r = atoi(tuple->value);
    color.g = color.r;
    color.b = color.r;
    component->darkness = color.r;
    sfSprite_setColor(component->sprite, color);
}

typedef struct {
    char *key;
    void (*setParam)(core_t *, graphics_t *, tuple_t *);
} graphicsParamsCtor_t;

const graphicsParamsCtor_t graphicsParamsCtors[] = {
    {"name", &setName},
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
    {"passed", &setPassed},
    {"parallax", &setParallax},
    {"velocity", &setVelocity},
    {"opacity", &setOpacity},
    {"darkness", &setDarkness}
};

comp_t *Graphics(core_t *core, FILE *fp)
{
    tuple_t *tuple = NULL;
    comp_t *comp = malloc(sizeof(comp_t));
    graphics_t *component = malloc(sizeof(graphics_t));

    if (comp == NULL || component == NULL)
        return NULL;
    component->name = NULL;
    component->sprite = NULL;
    component->animated = FALSE;
    component->parallax = FALSE;
    component->velocity = 0;
    component->elapsed = 0.f;
    component->passed = 0.f;
    component->opacity = 0;
    component->darkness = 255;
    component->pos = (sfVector2f){0, 0};
    component->size = (sfVector2f){0, 0};
    component->grid = (sfVector2f){0, 0};
    component->scale = (sfVector2f){0, 0};
    do {
        tuple = TupleFromFile(fp);
        if (tuple != NULL) {
            for (int i = 0; i < (int)(sizeof(graphicsParamsCtors) / sizeof(graphicsParamsCtor_t)); ++i)
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

void Dtr_Graphics(graphics_t *graphics)
{
    free(graphics->name);
    free(graphics);
}

void Graphics_updateSprite(core_t *core, graphics_t *graphic, char *path)
{
    sfVector2f pos = sfSprite_getPosition(graphic->sprite);
    sfVector2f scale = sfSprite_getScale(graphic->sprite);
    sfIntRect rect = sfSprite_getTextureRect(graphic->sprite);

    sfSprite_destroy(graphic->sprite);
    graphic->sprite = core->sprites->getSpriteByName(core->sprites, path);
    if (graphic->sprite == NULL)
        graphic->sprite = core->sprites->addSprite(core->sprites, path, path);
    sfSprite_setPosition(graphic->sprite, pos);
    sfSprite_setScale(graphic->sprite, scale);
    sfSprite_setTextureRect(graphic->sprite, rect);
}
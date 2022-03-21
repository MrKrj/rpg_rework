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

graphics_t *toGraphics(comp_t *comp)
{
    if (comp->type != GRAPHICS)
        return NULL;
    return (graphics_t *)comp->comp;
}

comp_t *Graphics(core_t *core, FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    comp_t *comp = malloc(sizeof(comp_t));
    graphics_t *component = malloc(sizeof(graphics_t));
    sfVector2f pos = {0, 0};
    sfVector2f size = {0, 0};

    if (comp == NULL || component == NULL)
        return NULL;
    getline(&line, &len, fp);
    line[strlen(line) - 1] = '\0';
    component->sprite = core->sprites->getSpriteByName(core->sprites, line);
    if (component->sprite == NULL)
        component->sprite = core->sprites->addSprite(core->sprites, line, line);
    getline(&line, &len, fp);
    pos.x = atof(line);
    getline(&line, &len, fp);
    pos.y = atof(line);
    sfSprite_setPosition(component->sprite, pos);
    getline(&line, &len, fp);
    size.x = atof(line);
    getline(&line, &len, fp);
    size.y = atof(line);
    sfSprite_setScale(component->sprite, size);
    getline(&line, &len, fp);
    comp->type = GRAPHICS;
    comp->comp = component;
    comp->next = NULL;
    return comp;
}
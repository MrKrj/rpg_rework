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

text_t *toText(comp_t *comp)
{
    if (comp->type != TEXT)
        return NULL;
    return (text_t *)comp->comp;
}

static void setFont(core_t *core, text_t *component, tuple_t *tuple)
{
    component->font = core->fonts->getFontByName(core->fonts, tuple->value);
    if (component->font == NULL)
        component->font = core->fonts->addFont(core->fonts, tuple->value, tuple->value);
}

static void setText(UNUSED core_t *core, text_t *component, tuple_t *tuple)
{
    if (component->font == NULL)
        return;
    component->text = sfText_create();
    sfText_setString(component->text, tuple->value);
    sfText_setFont(component->text, component->font);
}

static void setSize(UNUSED core_t *core, text_t *component, tuple_t *tuple)
{
    if (component->text == NULL)
        return;
    sfText_setCharacterSize(component->text, atoi(tuple->value));
}

static void setPosX(UNUSED core_t *core, text_t *component, tuple_t *tuple)
{
    if (component->text == NULL)
        return;
    sfVector2f pos = sfText_getPosition(component->text);
    pos.x = atof(tuple->value);
    sfText_setPosition(component->text, pos);
}

static void setPosY(UNUSED core_t *core, text_t *component, tuple_t *tuple)
{
    if (component->text == NULL)
        return;
    sfVector2f pos = sfText_getPosition(component->text);
    pos.y = atof(tuple->value);
    sfText_setPosition(component->text, pos);
}

static void setR(UNUSED core_t *core, text_t *component, tuple_t *tuple)
{
    if (component->text == NULL)
        return;
    sfColor color = sfText_getColor(component->text);
    color.r = atoi(tuple->value);
    sfText_setColor(component->text, color);
}

static void setG(UNUSED core_t *core, text_t *component, tuple_t *tuple)
{
    if (component->text == NULL)
        return;
    sfColor color = sfText_getColor(component->text);
    color.g = atoi(tuple->value);
    sfText_setColor(component->text, color);
}

static void setB(UNUSED core_t *core, text_t *component, tuple_t *tuple)
{
    if (component->text == NULL)
        return;
    sfColor color = sfText_getColor(component->text);
    color.b = atoi(tuple->value);
    sfText_setColor(component->text, color);
}

typedef struct {
    char *key;
    void (*setParam)(core_t *, text_t *, tuple_t *);
} textParamsCtor_t;

const textParamsCtor_t textParamsCtors[] = {
    {"font", &setFont},
    {"text", &setText},
    {"size", &setSize},
    {"posY", &setPosY},
    {"posX", &setPosX},
    {"r", &setR},
    {"g", &setG},
    {"b", &setB}
};

comp_t *Text(core_t *core, FILE *fp)
{
    tuple_t *tuple = NULL;
    comp_t *comp = malloc(sizeof(comp_t));
    text_t *component = malloc(sizeof(text_t));

    if (comp == NULL || component == NULL)
        return NULL;
    component->font = NULL;
    component->text = NULL;
    do {
        tuple = TupleFromFile(fp);
        if (tuple != NULL) {
            for (int i = 0; i < 6; ++i)
                if (strcmp(tuple->key, textParamsCtors[i].key) == 0)
                    textParamsCtors[i].setParam(core, component, tuple);
            Dtr_Tuple(tuple);
        }
    } while (tuple != NULL);
    comp->type = TEXT;
    comp->comp = component;
    comp->next = NULL;
    return comp;
}